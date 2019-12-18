#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; int /*<<< orphan*/  revents; int /*<<< orphan*/  events; } ;
struct fd {int /*<<< orphan*/  file; } ;
struct TYPE_4__ {int _key; } ;
typedef  TYPE_1__ poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLNVAL ; 
 int demangle_poll (int /*<<< orphan*/ ) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  mangle_poll (int) ; 
 int vfs_poll (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline __poll_t do_pollfd(struct pollfd *pollfd, poll_table *pwait,
				     bool *can_busy_poll,
				     __poll_t busy_flag)
{
	int fd = pollfd->fd;
	__poll_t mask = 0, filter;
	struct fd f;

	if (fd < 0)
		goto out;
	mask = EPOLLNVAL;
	f = fdget(fd);
	if (!f.file)
		goto out;

	/* userland u16 ->events contains POLL... bitmap */
	filter = demangle_poll(pollfd->events) | EPOLLERR | EPOLLHUP;
	pwait->_key = filter | busy_flag;
	mask = vfs_poll(f.file, pwait);
	if (mask & busy_flag)
		*can_busy_poll = true;
	mask &= filter;		/* Mask out unneeded events. */
	fdput(f);

out:
	/* ... and so does ->revents */
	pollfd->revents = mangle_poll(mask);
	return mask;
}