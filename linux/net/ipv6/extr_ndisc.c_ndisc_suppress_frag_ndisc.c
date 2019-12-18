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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ suppress_frag_ndisc; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 TYPE_2__* IP6CB (struct sk_buff*) ; 
 int IP6SKB_FRAGMENTED ; 
 struct inet6_dev* __in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*) ; 

__attribute__((used)) static bool ndisc_suppress_frag_ndisc(struct sk_buff *skb)
{
	struct inet6_dev *idev = __in6_dev_get(skb->dev);

	if (!idev)
		return true;
	if (IP6CB(skb)->flags & IP6SKB_FRAGMENTED &&
	    idev->cnf.suppress_frag_ndisc) {
		net_warn_ratelimited("Received fragmented ndisc packet. Carefully consider disabling suppress_frag_ndisc.\n");
		return true;
	}
	return false;
}