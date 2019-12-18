#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_1__* ops; } ;
struct msghdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  recvmsg; } ;

/* Variables and functions */
 int INDIRECT_CALL_INET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket*,struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inet6_recvmsg ; 
 int /*<<< orphan*/  inet_recvmsg ; 
 int /*<<< orphan*/  msg_data_left (struct msghdr*) ; 

__attribute__((used)) static inline int sock_recvmsg_nosec(struct socket *sock, struct msghdr *msg,
				     int flags)
{
	return INDIRECT_CALL_INET(sock->ops->recvmsg, inet6_recvmsg,
				  inet_recvmsg, sock, msg, msg_data_left(msg),
				  flags);
}