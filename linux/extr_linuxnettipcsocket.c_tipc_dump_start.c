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
struct netlink_callback {TYPE_1__* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int __tipc_dump_start (struct netlink_callback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

int tipc_dump_start(struct netlink_callback *cb)
{
	return __tipc_dump_start(cb, sock_net(cb->skb->sk));
}