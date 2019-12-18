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
typedef  int u16 ;
struct iovec {int* iov_base; int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SPLICE_F_GIFT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dprintf1 (char*,int) ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  pkey_access_deny (int) ; 
 int /*<<< orphan*/  pkey_assert (int) ; 
 int vmsplice (int,struct iovec*,int,int /*<<< orphan*/ ) ; 

void test_kernel_gup_of_access_disabled_region(int *ptr, u16 pkey)
{
	int pipe_ret, vmsplice_ret;
	struct iovec iov;
	int pipe_fds[2];

	pipe_ret = pipe(pipe_fds);

	pkey_assert(pipe_ret == 0);
	dprintf1("disabling access to PKEY[%02d], "
		 "having kernel vmsplice from buffer\n", pkey);
	pkey_access_deny(pkey);
	iov.iov_base = ptr;
	iov.iov_len = PAGE_SIZE;
	vmsplice_ret = vmsplice(pipe_fds[1], &iov, 1, SPLICE_F_GIFT);
	dprintf1("vmsplice() ret: %d\n", vmsplice_ret);
	pkey_assert(vmsplice_ret == -1);

	close(pipe_fds[0]);
	close(pipe_fds[1]);
}