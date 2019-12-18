#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct userfaultfd_ctx {int flags; } ;
struct TYPE_5__ {int ufd; } ;
struct TYPE_4__ {scalar_t__ reserved1; } ;
struct TYPE_6__ {TYPE_2__ fork; TYPE_1__ reserved; } ;
struct uffd_msg {TYPE_3__ arg; } ;

/* Variables and functions */
 int O_RDWR ; 
 int UFFD_SHARED_FCNTL_FLAGS ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct userfaultfd_ctx*,int) ; 
 int /*<<< orphan*/  userfaultfd_fops ; 

__attribute__((used)) static int resolve_userfault_fork(struct userfaultfd_ctx *ctx,
				  struct userfaultfd_ctx *new,
				  struct uffd_msg *msg)
{
	int fd;

	fd = anon_inode_getfd("[userfaultfd]", &userfaultfd_fops, new,
			      O_RDWR | (new->flags & UFFD_SHARED_FCNTL_FLAGS));
	if (fd < 0)
		return fd;

	msg->arg.reserved.reserved1 = 0;
	msg->arg.fork.ufd = fd;
	return 0;
}