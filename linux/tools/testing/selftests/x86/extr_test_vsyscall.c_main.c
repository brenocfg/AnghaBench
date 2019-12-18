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
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  init_vdso () ; 
 scalar_t__ init_vsys () ; 
 int /*<<< orphan*/  sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsegv ; 
 scalar_t__ test_emulation () ; 
 scalar_t__ test_getcpu (int) ; 
 scalar_t__ test_gtod () ; 
 scalar_t__ test_process_vm_readv () ; 
 scalar_t__ test_time () ; 
 scalar_t__ test_vsys_r () ; 
 scalar_t__ test_vsys_x () ; 

int main(int argc, char **argv)
{
	int nerrs = 0;

	init_vdso();
	nerrs += init_vsys();

	nerrs += test_gtod();
	nerrs += test_time();
	nerrs += test_getcpu(0);
	nerrs += test_getcpu(1);

	sethandler(SIGSEGV, sigsegv, 0);
	nerrs += test_vsys_r();
	nerrs += test_vsys_x();

	nerrs += test_process_vm_readv();

#ifdef __x86_64__
	nerrs += test_emulation();
#endif

	return nerrs ? 1 : 0;
}