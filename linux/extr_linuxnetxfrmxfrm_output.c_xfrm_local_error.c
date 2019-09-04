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
struct xfrm_state_afinfo {int /*<<< orphan*/  (* local_error ) (struct sk_buff*,int) ;} ;
struct sk_buff {scalar_t__ protocol; } ;

/* Variables and functions */
 unsigned int AF_INET ; 
 unsigned int AF_INET6 ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int) ; 
 struct xfrm_state_afinfo* xfrm_state_get_afinfo (unsigned int) ; 

void xfrm_local_error(struct sk_buff *skb, int mtu)
{
	unsigned int proto;
	struct xfrm_state_afinfo *afinfo;

	if (skb->protocol == htons(ETH_P_IP))
		proto = AF_INET;
	else if (skb->protocol == htons(ETH_P_IPV6))
		proto = AF_INET6;
	else
		return;

	afinfo = xfrm_state_get_afinfo(proto);
	if (afinfo) {
		afinfo->local_error(skb, mtu);
		rcu_read_unlock();
	}
}