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
typedef  int /*<<< orphan*/  regs ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  NT_PPC_TM_CVSX ; 
 int /*<<< orphan*/  PTRACE_GETREGSET ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  memcpy (unsigned long*,unsigned long*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iovec*) ; 

int show_vsx_ckpt(pid_t child, unsigned long *vsx)
{
	unsigned long regs[32];
	struct iovec iov;
	int ret;

	iov.iov_base = (u64 *) regs;
	iov.iov_len = sizeof(regs);
	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CVSX, &iov);
	if (ret) {
		perror("ptrace(PTRACE_GETREGSET, NT_PPC_TM_CVSX) failed");
		return TEST_FAIL;
	}
	memcpy(vsx, regs, sizeof(regs));
	return TEST_PASS;
}