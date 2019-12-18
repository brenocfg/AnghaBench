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
struct io_uring_sqe {int dummy; } ;
struct io_kiocb {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  __sys_sendmsg_sock ; 
 int io_send_recvmsg (struct io_kiocb*,struct io_uring_sqe const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_sendmsg(struct io_kiocb *req, const struct io_uring_sqe *sqe,
		      bool force_nonblock)
{
#if defined(CONFIG_NET)
	return io_send_recvmsg(req, sqe, force_nonblock, __sys_sendmsg_sock);
#else
	return -EOPNOTSUPP;
#endif
}