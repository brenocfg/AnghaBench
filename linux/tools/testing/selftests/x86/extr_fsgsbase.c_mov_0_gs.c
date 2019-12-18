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
 int /*<<< orphan*/  ARCH_GET_GS ; 
 int /*<<< orphan*/  ARCH_SET_GS ; 
 int /*<<< orphan*/  GS ; 
 int /*<<< orphan*/  SYS_arch_prctl ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,unsigned long,...) ; 
 unsigned long read_base (int /*<<< orphan*/ ) ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void mov_0_gs(unsigned long initial_base, bool schedule)
{
	unsigned long base, arch_base;

	printf("[RUN]\tARCH_SET_GS to 0x%lx then mov 0 to %%gs%s\n", initial_base, schedule ? " and schedule " : "");
	if (syscall(SYS_arch_prctl, ARCH_SET_GS, initial_base) != 0)
		err(1, "ARCH_SET_GS");

	if (schedule)
		usleep(10);

	asm volatile ("mov %0, %%gs" : : "rm" (0));
	base = read_base(GS);
	if (syscall(SYS_arch_prctl, ARCH_GET_GS, &arch_base) != 0)
		err(1, "ARCH_GET_GS");
	if (base == arch_base) {
		printf("[OK]\tGSBASE is 0x%lx\n", base);
	} else {
		nerrs++;
		printf("[FAIL]\tGSBASE changed to 0x%lx but kernel reports 0x%lx\n", base, arch_base);
	}
}