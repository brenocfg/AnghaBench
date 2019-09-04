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
struct socket {int dummy; } ;
struct iov_iter {int dummy; } ;
struct msghdr {struct iov_iter msg_iter; int /*<<< orphan*/  msg_flags; struct kiocb* msg_iocb; } ;
struct kiocb {scalar_t__ ki_pos; struct file* ki_filp; } ;
struct file {int f_flags; struct socket* private_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESPIPE ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  sock_recvmsg (struct socket*,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t sock_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct file *file = iocb->ki_filp;
	struct socket *sock = file->private_data;
	struct msghdr msg = {.msg_iter = *to,
			     .msg_iocb = iocb};
	ssize_t res;

	if (file->f_flags & O_NONBLOCK)
		msg.msg_flags = MSG_DONTWAIT;

	if (iocb->ki_pos != 0)
		return -ESPIPE;

	if (!iov_iter_count(to))	/* Match SYS5 behaviour */
		return 0;

	res = sock_recvmsg(sock, &msg, msg.msg_flags);
	*to = msg.msg_iter;
	return res;
}