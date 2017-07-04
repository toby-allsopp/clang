// RUN: %clang_cc1 -triple x86_64-apple-darwin9 %s -std=c++1z -fcoroutines-ts -fsyntax-only -Wall -Wextra -Wuninitialized  -fblocks
#include "Inputs/std-coroutine.h"

using namespace std::experimental;

struct coro_t {};

struct coro_promise_type {
  coro_t get_return_object() { return {}; }
  suspend_never initial_suspend() { return {}; }
  suspend_never final_suspend() { return {}; }
  void return_void() {}
  static void unhandled_exception() {}
};

struct C {
  coro_t f();
};

namespace std::experimental {
  template<>
  struct coroutine_traits<coro_t, C*> {
    using promise_type = coro_promise_type;
  };
}

coro_t C::f() {
  co_return;
}

int main() {
  C c;
  c.f();
}
