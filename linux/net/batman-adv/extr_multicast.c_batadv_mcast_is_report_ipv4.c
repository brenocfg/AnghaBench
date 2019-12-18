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
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  IGMPV2_HOST_MEMBERSHIP_REPORT 130 
#define  IGMPV3_HOST_MEMBERSHIP_REPORT 129 
#define  IGMP_HOST_MEMBERSHIP_REPORT 128 
 TYPE_1__* igmp_hdr (struct sk_buff*) ; 
 scalar_t__ ip_mc_check_igmp (struct sk_buff*) ; 

__attribute__((used)) static bool batadv_mcast_is_report_ipv4(struct sk_buff *skb)
{
	if (ip_mc_check_igmp(skb) < 0)
		return false;

	switch (igmp_hdr(skb)->type) {
	case IGMP_HOST_MEMBERSHIP_REPORT:
	case IGMPV2_HOST_MEMBERSHIP_REPORT:
	case IGMPV3_HOST_MEMBERSHIP_REPORT:
		return true;
	}

	return false;
}