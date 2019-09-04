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
struct pt_regs {unsigned long* gpr; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_GETREGS ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pt_regs*) ; 

int show_gpr(pid_t child, unsigned long *gpr)
{
	struct pt_regs *regs;
	int ret, i;

	regs = (struct pt_regs *) malloc(sizeof(struct pt_regs));
	if (!regs) {
		perror("malloc() failed");
		return TEST_FAIL;
	}

	ret = ptrace(PTRACE_GETREGS, child, NULL, regs);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		return TEST_FAIL;
	}

	if (gpr) {
		for (i = 14; i < 32; i++)
			gpr[i-14] = regs->gpr[i];
	}

	return TEST_PASS;
}