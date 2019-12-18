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

__attribute__((used)) static void check_gs_value(unsigned long value)
{
	unsigned long base;
	unsigned short sel;

	printf("[RUN]\tARCH_SET_GS to 0x%lx\n", value);
	if (syscall(SYS_arch_prctl, ARCH_SET_GS, value) != 0)
		err(1, "ARCH_SET_GS");

	asm volatile ("mov %%gs, %0" : "=rm" (sel));
	base = read_base(GS);
	if (base == value) {
		printf("[OK]\tGSBASE was set as expected (selector 0x%hx)\n",
		       sel);
	} else {
		nerrs++;
		printf("[FAIL]\tGSBASE was not as expected: got 0x%lx (selector 0x%hx)\n",
		       base, sel);
	}

	if (syscall(SYS_arch_prctl, ARCH_GET_GS, &base) != 0)
		err(1, "ARCH_GET_GS");
	if (base == value) {
		printf("[OK]\tARCH_GET_GS worked as expected (selector 0x%hx)\n",
		       sel);
	} else {
		nerrs++;
		printf("[FAIL]\tARCH_GET_GS was not as expected: got 0x%lx (selector 0x%hx)\n",
		       base, sel);
	}
}