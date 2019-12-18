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
 int /*<<< orphan*/  _bss_end ; 
 int /*<<< orphan*/  _bss_start ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int* stack ; 
 int stack_end ; 
 int /*<<< orphan*/  stub_main1 () ; 

void stub_main(void) {
  memset(&_bss_start, 0, (&_bss_end - &_bss_start));
  __asm volatile("movi a1, stack_end\n");
  stub_main1();
  // Keep the stack vars alive.
  stack[0] = stack_end = 0xff;
}