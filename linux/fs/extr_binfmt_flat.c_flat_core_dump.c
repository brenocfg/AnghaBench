#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct coredump_params {TYPE_1__* siginfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_signo; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flat_core_dump(struct coredump_params *cprm)
{
	pr_warn("Process %s:%d received signr %d and should have core dumped\n",
		current->comm, current->pid, cprm->siginfo->si_signo);
	return 1;
}