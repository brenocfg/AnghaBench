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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int _NSIG ; 
 int /*<<< orphan*/  __NR_io_uring_enter ; 
 int syscall (int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *,int) ; 

int io_uring_enter(int fd, unsigned int to_submit, unsigned int min_complete,
		   unsigned int flags, sigset_t *sig)
{
	return syscall(__NR_io_uring_enter, fd, to_submit, min_complete,
			flags, sig, _NSIG / 8);
}