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
 int security_socket_sendmsg (struct socket*,struct msghdr*,int /*<<< orphan*/ ) ; 
 int sock_sendmsg_nosec (struct socket*,struct msghdr*) ; 

int sock_sendmsg(struct socket *sock, struct msghdr *msg)
{
	int err = security_socket_sendmsg(sock, msg,
					  msg_data_left(msg));

	return err ?: sock_sendmsg_nosec(sock, msg);
}