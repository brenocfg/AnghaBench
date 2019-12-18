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
 int /*<<< orphan*/  SIGTRAP ; 
 int X86_EFLAGS_NT ; 
 int X86_EFLAGS_TF ; 
 int /*<<< orphan*/  do_it (int) ; 
 scalar_t__ nerrs ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigtrap ; 

int main(void)
{
	printf("[RUN]\tSet NT and issue a syscall\n");
	do_it(X86_EFLAGS_NT);

	/*
	 * Now try it again with TF set -- TF forces returns via IRET in all
	 * cases except non-ptregs-using 64-bit full fast path syscalls.
	 */

	sethandler(SIGTRAP, sigtrap, 0);

	printf("[RUN]\tSet NT|TF and issue a syscall\n");
	do_it(X86_EFLAGS_NT | X86_EFLAGS_TF);

	return nerrs == 0 ? 0 : 1;
}