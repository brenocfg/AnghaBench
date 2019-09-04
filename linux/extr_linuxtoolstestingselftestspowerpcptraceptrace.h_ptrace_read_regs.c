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
struct iovec {unsigned long* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_GETREGSET ; 
 int TEST_PASS ; 
 long ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,struct iovec*) ; 
 int /*<<< orphan*/  start_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_trace (int /*<<< orphan*/ ) ; 

int ptrace_read_regs(pid_t child, unsigned long type, unsigned long regs[],
		     int n)
{
	struct iovec iov;
	long ret;

	FAIL_IF(start_trace(child));

	iov.iov_base = regs;
	iov.iov_len = n * sizeof(unsigned long);

	ret = ptrace(PTRACE_GETREGSET, child, type, &iov);
	if (ret)
		return ret;

	FAIL_IF(stop_trace(child));

	return TEST_PASS;
}