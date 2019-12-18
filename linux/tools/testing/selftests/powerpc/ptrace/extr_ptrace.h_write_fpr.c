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
struct fpr_regs {unsigned long* fpr; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_GETFPREGS ; 
 int /*<<< orphan*/  PTRACE_SETFPREGS ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fpr_regs*) ; 

int write_fpr(pid_t child, unsigned long val)
{
	struct fpr_regs *regs;
	int ret, i;

	regs = (struct fpr_regs *) malloc(sizeof(struct fpr_regs));
	ret = ptrace(PTRACE_GETFPREGS, child, NULL, regs);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		return TEST_FAIL;
	}

	for (i = 0; i < 32; i++)
		regs->fpr[i] = val;

	ret = ptrace(PTRACE_SETFPREGS, child, NULL, regs);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		return TEST_FAIL;
	}
	return TEST_PASS;
}