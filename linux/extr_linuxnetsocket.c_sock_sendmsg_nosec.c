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
struct TYPE_2__ {int (* sendmsg ) (struct socket*,struct msghdr*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIOCBQUEUED ; 
 int /*<<< orphan*/  msg_data_left (struct msghdr*) ; 
 int stub1 (struct socket*,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sock_sendmsg_nosec(struct socket *sock, struct msghdr *msg)
{
	int ret = sock->ops->sendmsg(sock, msg, msg_data_left(msg));
	BUG_ON(ret == -EIOCBQUEUED);
	return ret;
}