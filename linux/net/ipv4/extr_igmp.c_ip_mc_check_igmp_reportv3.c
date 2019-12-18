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
struct igmpv3_report {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ip_mc_may_pull (struct sk_buff*,unsigned int) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static int ip_mc_check_igmp_reportv3(struct sk_buff *skb)
{
	unsigned int len = skb_transport_offset(skb);

	len += sizeof(struct igmpv3_report);

	return ip_mc_may_pull(skb, len) ? 0 : -EINVAL;
}