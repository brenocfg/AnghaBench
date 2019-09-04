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
 int /*<<< orphan*/  ARCH_SET_GS ; 
 unsigned long HARD_ZERO ; 
 int /*<<< orphan*/  SYS_arch_prctl ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,char*,unsigned short) ; 
 unsigned long remote_base ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void do_remote_base()
{
	unsigned long to_set = remote_base;
	bool hard_zero = false;
	if (to_set == HARD_ZERO) {
		to_set = 0;
		hard_zero = true;
	}

	if (syscall(SYS_arch_prctl, ARCH_SET_GS, to_set) != 0)
		err(1, "ARCH_SET_GS");

	if (hard_zero)
		asm volatile ("mov %0, %%gs" : : "rm" ((unsigned short)0));

	unsigned short sel;
	asm volatile ("mov %%gs, %0" : "=rm" (sel));
	printf("\tother thread: ARCH_SET_GS(0x%lx)%s -- sel is 0x%hx\n",
	       to_set, hard_zero ? " and clear gs" : "", sel);
}