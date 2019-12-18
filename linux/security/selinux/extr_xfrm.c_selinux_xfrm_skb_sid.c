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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ SECSID_NULL ; 
 scalar_t__ selinux_xfrm_skb_sid_egress (struct sk_buff*) ; 
 int selinux_xfrm_skb_sid_ingress (struct sk_buff*,scalar_t__*,int /*<<< orphan*/ ) ; 

int selinux_xfrm_skb_sid(struct sk_buff *skb, u32 *sid)
{
	int rc;

	rc = selinux_xfrm_skb_sid_ingress(skb, sid, 0);
	if (rc == 0 && *sid == SECSID_NULL)
		*sid = selinux_xfrm_skb_sid_egress(skb);

	return rc;
}