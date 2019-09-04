#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

void abort(void) {
  /* cause an unaligned access exception, that will drop you into gdb */
  *(int *) 1 = 1;
  while (1)
    ; /* avoid gcc warning because stdlib abort() has noreturn attribute */
}