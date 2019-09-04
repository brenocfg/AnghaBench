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
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msg_data_left (struct msghdr*) ; 
 int security_socket_recvmsg (struct socket*,struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int sock_recvmsg_nosec (struct socket*,struct msghdr*,int) ; 

int sock_recvmsg(struct socket *sock, struct msghdr *msg, int flags)
{
	int err = security_socket_recvmsg(sock, msg, msg_data_left(msg), flags);

	return err ?: sock_recvmsg_nosec(sock, msg, flags);
}