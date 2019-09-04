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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;
struct tipc_media_addr {int dummy; } ;
struct tipc_bearer {TYPE_1__* media; int /*<<< orphan*/  up; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_msg ) (struct net*,struct sk_buff*,struct tipc_bearer*,struct tipc_media_addr*) ;} ;

/* Variables and functions */
 struct tipc_bearer* bearer_get (struct net*,int /*<<< orphan*/ ) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ msg_is_reset (struct tipc_msg*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct net*,struct sk_buff*,struct tipc_bearer*,struct tipc_media_addr*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void tipc_bearer_xmit_skb(struct net *net, u32 bearer_id,
			  struct sk_buff *skb,
			  struct tipc_media_addr *dest)
{
	struct tipc_msg *hdr = buf_msg(skb);
	struct tipc_bearer *b;

	rcu_read_lock();
	b = bearer_get(net, bearer_id);
	if (likely(b && (test_bit(0, &b->up) || msg_is_reset(hdr))))
		b->media->send_msg(net, skb, b, dest);
	else
		kfree_skb(skb);
	rcu_read_unlock();
}