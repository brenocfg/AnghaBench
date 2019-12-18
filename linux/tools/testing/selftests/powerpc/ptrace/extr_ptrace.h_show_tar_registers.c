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
 int /*<<< orphan*/  NT_PPC_DSCR ; 
 int /*<<< orphan*/  NT_PPC_PPR ; 
 int /*<<< orphan*/  NT_PPC_TAR ; 
 int /*<<< orphan*/  PTRACE_GETREGSET ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 unsigned long* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iovec*) ; 

int show_tar_registers(pid_t child, unsigned long *out)
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

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TAR, &iov);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		goto fail;
	}
	if (out)
		out[0] = *reg;

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_PPR, &iov);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		goto fail;
	}
	if (out)
		out[1] = *reg;

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_DSCR, &iov);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET) failed");
		goto fail;
	}
	if (out)
		out[2] = *reg;

	free(reg);
	return TEST_PASS;
fail:
	free(reg);
	return TEST_FAIL;
}