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
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 int ENOMSG ; 
 scalar_t__ IPPROTO_IGMP ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int ip_mc_check_igmp_csum (struct sk_buff*) ; 
 int ip_mc_check_igmp_msg (struct sk_buff*) ; 
 int ip_mc_check_iphdr (struct sk_buff*) ; 

int ip_mc_check_igmp(struct sk_buff *skb)
{
	int ret = ip_mc_check_iphdr(skb);

	if (ret < 0)
		return ret;

	if (ip_hdr(skb)->protocol != IPPROTO_IGMP)
		return -ENOMSG;

	ret = ip_mc_check_igmp_csum(skb);
	if (ret < 0)
		return ret;

	return ip_mc_check_igmp_msg(skb);
}