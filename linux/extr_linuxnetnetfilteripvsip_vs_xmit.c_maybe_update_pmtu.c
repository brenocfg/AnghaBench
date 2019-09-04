#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; struct sock* sk; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct rtable {TYPE_2__ dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_pmtu ) (TYPE_2__*,struct sock*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 scalar_t__ sk_fullsock (struct sock*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct sock*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void maybe_update_pmtu(int skb_af, struct sk_buff *skb, int mtu)
{
	struct sock *sk = skb->sk;
	struct rtable *ort = skb_rtable(skb);

	if (!skb->dev && sk && sk_fullsock(sk))
		ort->dst.ops->update_pmtu(&ort->dst, sk, NULL, mtu);
}