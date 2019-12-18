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
struct msghdr {int /*<<< orphan*/  msg_iter; int /*<<< orphan*/  msg_flags; } ;
struct kvec {size_t iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,size_t) ; 
 int sock_recvmsg (struct socket*,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int o2net_recv_tcp_msg(struct socket *sock, void *data, size_t len)
{
	struct kvec vec = { .iov_len = len, .iov_base = data, };
	struct msghdr msg = { .msg_flags = MSG_DONTWAIT, };
	iov_iter_kvec(&msg.msg_iter, READ, &vec, 1, len);
	return sock_recvmsg(sock, &msg, MSG_DONTWAIT);
}