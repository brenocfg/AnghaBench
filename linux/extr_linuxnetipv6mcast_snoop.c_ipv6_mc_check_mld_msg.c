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
struct mld_msg {int mld_type; } ;

/* Variables and functions */
 int ENOMSG ; 
#define  ICMPV6_MGM_QUERY 131 
#define  ICMPV6_MGM_REDUCTION 130 
#define  ICMPV6_MGM_REPORT 129 
#define  ICMPV6_MLD2_REPORT 128 
 int ipv6_mc_check_mld_query (struct sk_buff*) ; 
 int ipv6_mc_check_mld_reportv2 (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int ipv6_mc_check_mld_msg(struct sk_buff *skb)
{
	struct mld_msg *mld = (struct mld_msg *)skb_transport_header(skb);

	switch (mld->mld_type) {
	case ICMPV6_MGM_REDUCTION:
	case ICMPV6_MGM_REPORT:
		/* fall through */
		return 0;
	case ICMPV6_MLD2_REPORT:
		return ipv6_mc_check_mld_reportv2(skb);
	case ICMPV6_MGM_QUERY:
		return ipv6_mc_check_mld_query(skb);
	default:
		return -ENOMSG;
	}
}