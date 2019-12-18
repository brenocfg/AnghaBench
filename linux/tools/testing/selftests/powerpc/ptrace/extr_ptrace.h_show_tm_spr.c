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
typedef  int /*<<< orphan*/  u64 ;
struct tm_spr_regs {int dummy; } ;
struct iovec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  NT_PPC_TM_SPR ; 
 int /*<<< orphan*/  PTRACE_GETREGSET ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct tm_spr_regs*,struct tm_spr_regs*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iovec*) ; 

int show_tm_spr(pid_t child, struct tm_spr_regs *out)
{
	struct tm_spr_regs *regs;
	struct iovec iov;
	int ret;

	regs = (struct tm_spr_regs *) malloc(sizeof(struct tm_spr_regs));
	if (!regs) {
		perror("malloc() failed");
		return TEST_FAIL;
	}

	iov.iov_base = (u64 *) regs;
	iov.iov_len = sizeof(struct tm_spr_regs);

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_SPR, &iov);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		return TEST_FAIL;
	}

	if (out)
		memcpy(out, regs, sizeof(struct tm_spr_regs));

	return TEST_PASS;
}