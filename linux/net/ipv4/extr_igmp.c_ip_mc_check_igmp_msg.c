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
 int ENOMSG ; 
#define  IGMPV2_HOST_MEMBERSHIP_REPORT 132 
#define  IGMPV3_HOST_MEMBERSHIP_REPORT 131 
#define  IGMP_HOST_LEAVE_MESSAGE 130 
#define  IGMP_HOST_MEMBERSHIP_QUERY 129 
#define  IGMP_HOST_MEMBERSHIP_REPORT 128 
 TYPE_1__* igmp_hdr (struct sk_buff*) ; 
 int ip_mc_check_igmp_query (struct sk_buff*) ; 
 int ip_mc_check_igmp_reportv3 (struct sk_buff*) ; 

__attribute__((used)) static int ip_mc_check_igmp_msg(struct sk_buff *skb)
{
	switch (igmp_hdr(skb)->type) {
	case IGMP_HOST_LEAVE_MESSAGE:
	case IGMP_HOST_MEMBERSHIP_REPORT:
	case IGMPV2_HOST_MEMBERSHIP_REPORT:
		return 0;
	case IGMPV3_HOST_MEMBERSHIP_REPORT:
		return ip_mc_check_igmp_reportv3(skb);
	case IGMP_HOST_MEMBERSHIP_QUERY:
		return ip_mc_check_igmp_query(skb);
	default:
		return -ENOMSG;
	}
}