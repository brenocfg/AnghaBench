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
struct sk_buff {int dummy; } ;
struct netlink_sock {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int NETLINK_F_STRICT_CHK ; 
 struct netlink_sock* nlk_sk (int /*<<< orphan*/ ) ; 

bool netlink_strict_get_check(struct sk_buff *skb)
{
	const struct netlink_sock *nlk = nlk_sk(NETLINK_CB(skb).sk);

	return nlk->flags & NETLINK_F_STRICT_CHK;
}