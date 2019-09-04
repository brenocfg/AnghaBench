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
struct ptrace_peeksiginfo_args {int /*<<< orphan*/  flags; scalar_t__ off; int /*<<< orphan*/  nr; } ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ EFAULT ; 
 scalar_t__ EINVAL ; 
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int PAGE_SIZE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  PTRACE_PEEKSIGINFO ; 
 int /*<<< orphan*/  SIGNR ; 
 int /*<<< orphan*/  err (char*,...) ; 
 scalar_t__ errno ; 
 void* mmap (void*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int sys_ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ptrace_peeksiginfo_args*,void*) ; 

__attribute__((used)) static int check_error_paths(pid_t child)
{
	struct ptrace_peeksiginfo_args arg;
	int ret, exit_code = -1;
	void *addr_rw, *addr_ro;

	/*
	 * Allocate two contiguous pages. The first one is for read-write,
	 * another is for read-only.
	 */
	addr_rw = mmap(NULL, 2 * PAGE_SIZE, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (addr_rw == MAP_FAILED) {
		err("mmap() failed: %m\n");
		return 1;
	}

	addr_ro = mmap(addr_rw + PAGE_SIZE, PAGE_SIZE, PROT_READ,
			MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
	if (addr_ro == MAP_FAILED) {
		err("mmap() failed: %m\n");
		goto out;
	}

	arg.nr = SIGNR;
	arg.off = 0;

	/* Unsupported flags */
	arg.flags = ~0;
	ret = sys_ptrace(PTRACE_PEEKSIGINFO, child, &arg, addr_rw);
	if (ret != -1 || errno != EINVAL) {
		err("sys_ptrace() returns %d (expected -1),"
				" errno %d (expected %d): %m\n",
				ret, errno, EINVAL);
		goto out;
	}
	arg.flags = 0;

	/* A part of the buffer is read-only */
	ret = sys_ptrace(PTRACE_PEEKSIGINFO, child, &arg,
					addr_ro - sizeof(siginfo_t) * 2);
	if (ret != 2) {
		err("sys_ptrace() returns %d (expected 2): %m\n", ret);
		goto out;
	}

	/* Read-only buffer */
	ret = sys_ptrace(PTRACE_PEEKSIGINFO, child, &arg, addr_ro);
	if (ret != -1 && errno != EFAULT) {
		err("sys_ptrace() returns %d (expected -1),"
				" errno %d (expected %d): %m\n",
				ret, errno, EFAULT);
		goto out;
	}

	exit_code = 0;
out:
	munmap(addr_rw, 2 * PAGE_SIZE);
	return exit_code;
}