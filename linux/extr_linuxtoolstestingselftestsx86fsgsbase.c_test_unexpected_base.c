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
 int /*<<< orphan*/  FUTEX_WAIT ; 
 int /*<<< orphan*/  FUTEX_WAKE ; 
 int /*<<< orphan*/  GS ; 
 int /*<<< orphan*/  SYS_arch_prctl ; 
 int /*<<< orphan*/  SYS_futex ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ftx ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned long read_base (int /*<<< orphan*/ ) ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void test_unexpected_base(void)
{
	unsigned long base;

	printf("[RUN]\tARCH_SET_GS(0), clear gs, then manipulate GSBASE in a different thread\n");
	if (syscall(SYS_arch_prctl, ARCH_SET_GS, 0) != 0)
		err(1, "ARCH_SET_GS");
	asm volatile ("mov %0, %%gs" : : "rm" ((unsigned short)0));

	ftx = 2;
	syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, NULL, NULL, 0);
	while (ftx != 0)
		syscall(SYS_futex, &ftx, FUTEX_WAIT, 1, NULL, NULL, 0);

	base = read_base(GS);
	if (base == 0) {
		printf("[OK]\tGSBASE remained 0\n");
	} else {
		nerrs++;
		printf("[FAIL]\tGSBASE changed to 0x%lx\n", base);
	}
}