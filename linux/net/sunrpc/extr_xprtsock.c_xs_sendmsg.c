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
struct msghdr {int /*<<< orphan*/  msg_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  iov_iter_advance (int /*<<< orphan*/ *,size_t) ; 
 int sock_sendmsg (struct socket*,struct msghdr*) ; 

__attribute__((used)) static int xs_sendmsg(struct socket *sock, struct msghdr *msg, size_t seek)
{
	if (seek)
		iov_iter_advance(&msg->msg_iter, seek);
	return sock_sendmsg(sock, msg);
}