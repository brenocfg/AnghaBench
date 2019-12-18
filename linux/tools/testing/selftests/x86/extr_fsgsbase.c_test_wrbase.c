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
 int /*<<< orphan*/  FUTEX_WAIT ; 
 int /*<<< orphan*/  FUTEX_WAKE ; 
 int /*<<< orphan*/  SYS_futex ; 
 int ftx ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned long rdgsbase () ; 
 scalar_t__ remote_base ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrgsbase (unsigned long) ; 

void test_wrbase(unsigned short index, unsigned long base)
{
	unsigned short newindex;
	unsigned long newbase;

	printf("[RUN]\tGS = 0x%hx, GSBASE = 0x%lx\n", index, base);

	asm volatile ("mov %0, %%gs" : : "rm" (index));
	wrgsbase(base);

	remote_base = 0;
	ftx = 1;
	syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, NULL, NULL, 0);
	while (ftx != 0)
		syscall(SYS_futex, &ftx, FUTEX_WAIT, 1, NULL, NULL, 0);

	asm volatile ("mov %%gs, %0" : "=rm" (newindex));
	newbase = rdgsbase();

	if (newindex == index && newbase == base) {
		printf("[OK]\tIndex and base were preserved\n");
	} else {
		printf("[FAIL]\tAfter switch, GS = 0x%hx and GSBASE = 0x%lx\n",
		       newindex, newbase);
		nerrs++;
	}
}