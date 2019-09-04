#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ptrace_peeksiginfo_args {int nr; int off; scalar_t__ flags; } ;
struct TYPE_3__ {int si_code; int si_int; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_PEEKSIGINFO ; 
 scalar_t__ PTRACE_PEEKSIGINFO_SHARED ; 
 int SIGNR ; 
 int TEST_SICODE_PRIV ; 
 int TEST_SICODE_SHARE ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int sys_ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ptrace_peeksiginfo_args*,TYPE_1__*) ; 

int check_direct_path(pid_t child, int shared, int nr)
{
	struct ptrace_peeksiginfo_args arg = {.flags = 0, .nr = nr, .off = 0};
	int i, j, ret, exit_code = -1;
	siginfo_t siginfo[SIGNR];
	int si_code;

	if (shared == 1) {
		arg.flags = PTRACE_PEEKSIGINFO_SHARED;
		si_code = TEST_SICODE_SHARE;
	} else {
		arg.flags = 0;
		si_code = TEST_SICODE_PRIV;
	}

	for (i = 0; i < SIGNR; ) {
		arg.off = i;
		ret = sys_ptrace(PTRACE_PEEKSIGINFO, child, &arg, siginfo);
		if (ret == -1) {
			err("ptrace() failed: %m\n");
			goto out;
		}

		if (ret == 0)
			break;

		for (j = 0; j < ret; j++, i++) {
			if (siginfo[j].si_code == si_code &&
			    siginfo[j].si_int == i)
				continue;

			err("%d: Wrong siginfo i=%d si_code=%d si_int=%d\n",
			     shared, i, siginfo[j].si_code, siginfo[j].si_int);
			goto out;
		}
	}

	if (i != SIGNR) {
		err("Only %d signals were read\n", i);
		goto out;
	}

	exit_code = 0;
out:
	return exit_code;
}