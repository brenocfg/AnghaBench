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
struct xt_ecn_info {int ip_ect; int invert; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int* flow_lbl; } ;

/* Variables and functions */
 int XT_ECN_IP_MASK ; 
 int XT_ECN_OP_MATCH_IP ; 
 TYPE_1__* ipv6_hdr (struct sk_buff const*) ; 

__attribute__((used)) static inline bool match_ipv6(const struct sk_buff *skb,
			      const struct xt_ecn_info *einfo)
{
	return (((ipv6_hdr(skb)->flow_lbl[0] >> 4) & XT_ECN_IP_MASK) ==
	        einfo->ip_ect) ^
	       !!(einfo->invert & XT_ECN_OP_MATCH_IP);
}