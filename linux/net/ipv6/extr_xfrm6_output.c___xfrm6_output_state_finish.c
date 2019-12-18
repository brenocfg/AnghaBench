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
struct xfrm_state_afinfo {int (* output_finish ) (struct sock*,struct sk_buff*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  family; } ;
struct xfrm_state {TYPE_1__ outer_mode; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (struct xfrm_state_afinfo const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (struct sock*,struct sk_buff*) ; 
 struct xfrm_state_afinfo* xfrm_state_afinfo_get_rcu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __xfrm6_output_state_finish(struct xfrm_state *x, struct sock *sk,
				       struct sk_buff *skb)
{
	const struct xfrm_state_afinfo *afinfo;
	int ret = -EAFNOSUPPORT;

	rcu_read_lock();
	afinfo = xfrm_state_afinfo_get_rcu(x->outer_mode.family);
	if (likely(afinfo))
		ret = afinfo->output_finish(sk, skb);
	else
		kfree_skb(skb);
	rcu_read_unlock();

	return ret;
}