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
struct sk_buff {int dummy; } ;
struct netlink_callback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tipc_add_sock_diag ; 
 int tipc_nl_sk_walk (struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tipc_diag_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	return tipc_nl_sk_walk(skb, cb, __tipc_add_sock_diag);
}