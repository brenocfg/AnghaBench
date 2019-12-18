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
struct iovec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  NT_PPC_TM_CDSCR ; 
 int /*<<< orphan*/  NT_PPC_TM_CPPR ; 
 int /*<<< orphan*/  NT_PPC_TM_CTAR ; 
 int /*<<< orphan*/  PTRACE_SETREGSET ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 unsigned long* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iovec*) ; 

int write_ckpt_tar_registers(pid_t child, unsigned long tar,
		unsigned long ppr, unsigned long dscr)
{
	struct iovec iov;
	unsigned long *reg;
	int ret;

	reg = malloc(sizeof(unsigned long));
	if (!reg) {
		perror("malloc() failed");
		return TEST_FAIL;
	}

	iov.iov_base = (u64 *) reg;
	iov.iov_len = sizeof(unsigned long);

	*reg = tar;
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CTAR, &iov);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		goto fail;
	}

	*reg = ppr;
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CPPR, &iov);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		goto fail;
	}

	*reg = dscr;
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CDSCR, &iov);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		goto fail;
	}

	free(reg);
	return TEST_PASS;
fail:
	free(reg);
	return TEST_FAIL;
}