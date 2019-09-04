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
struct TYPE_2__ {int /*<<< orphan*/  tunnel_id; } ;
struct net_bridge_vlan {scalar_t__ vid; TYPE_1__ tinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_VLAN_INFO_RANGE_BEGIN ; 
 int /*<<< orphan*/  BRIDGE_VLAN_INFO_RANGE_END ; 
 int br_fill_vlan_tinfo (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int br_fill_vlan_tinfo_range(struct sk_buff *skb,
				    struct net_bridge_vlan *vtbegin,
				    struct net_bridge_vlan *vtend)
{
	int err;

	if (vtend && (vtend->vid - vtbegin->vid) > 0) {
		/* add range to skb */
		err = br_fill_vlan_tinfo(skb, vtbegin->vid,
					 vtbegin->tinfo.tunnel_id,
					 BRIDGE_VLAN_INFO_RANGE_BEGIN);
		if (err)
			return err;

		err = br_fill_vlan_tinfo(skb, vtend->vid,
					 vtend->tinfo.tunnel_id,
					 BRIDGE_VLAN_INFO_RANGE_END);
		if (err)
			return err;
	} else {
		err = br_fill_vlan_tinfo(skb, vtbegin->vid,
					 vtbegin->tinfo.tunnel_id,
					 0);
		if (err)
			return err;
	}

	return 0;
}