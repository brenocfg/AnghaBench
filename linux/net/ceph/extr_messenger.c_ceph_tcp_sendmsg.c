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
struct msghdr {int msg_flags; } ;
struct kvec {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MSG_DONTWAIT ; 
 int MSG_EOR ; 
 int MSG_MORE ; 
 int MSG_NOSIGNAL ; 
 int kernel_sendmsg (struct socket*,struct msghdr*,struct kvec*,size_t,size_t) ; 

__attribute__((used)) static int ceph_tcp_sendmsg(struct socket *sock, struct kvec *iov,
			    size_t kvlen, size_t len, bool more)
{
	struct msghdr msg = { .msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL };
	int r;

	if (more)
		msg.msg_flags |= MSG_MORE;
	else
		msg.msg_flags |= MSG_EOR;  /* superfluous, but what the hell */

	r = kernel_sendmsg(sock, &msg, iov, kvlen, len);
	if (r == -EAGAIN)
		r = 0;
	return r;
}