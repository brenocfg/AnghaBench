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
struct file {int dummy; } ;
struct eventpoll {struct file* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int EPOLL_CLOEXEC ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int PTR_ERR (struct file*) ; 
 struct file* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct eventpoll*,int) ; 
 int ep_alloc (struct eventpoll**) ; 
 int /*<<< orphan*/  ep_free (struct eventpoll*) ; 
 int /*<<< orphan*/  eventpoll_fops ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int get_unused_fd_flags (int) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 

__attribute__((used)) static int do_epoll_create(int flags)
{
	int error, fd;
	struct eventpoll *ep = NULL;
	struct file *file;

	/* Check the EPOLL_* constant for consistency.  */
	BUILD_BUG_ON(EPOLL_CLOEXEC != O_CLOEXEC);

	if (flags & ~EPOLL_CLOEXEC)
		return -EINVAL;
	/*
	 * Create the internal data structure ("struct eventpoll").
	 */
	error = ep_alloc(&ep);
	if (error < 0)
		return error;
	/*
	 * Creates all the items needed to setup an eventpoll file. That is,
	 * a file structure and a free file descriptor.
	 */
	fd = get_unused_fd_flags(O_RDWR | (flags & O_CLOEXEC));
	if (fd < 0) {
		error = fd;
		goto out_free_ep;
	}
	file = anon_inode_getfile("[eventpoll]", &eventpoll_fops, ep,
				 O_RDWR | (flags & O_CLOEXEC));
	if (IS_ERR(file)) {
		error = PTR_ERR(file);
		goto out_free_fd;
	}
	ep->file = file;
	fd_install(fd, file);
	return fd;

out_free_fd:
	put_unused_fd(fd);
out_free_ep:
	ep_free(ep);
	return error;
}