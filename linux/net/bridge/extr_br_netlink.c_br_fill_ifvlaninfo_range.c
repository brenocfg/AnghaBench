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
typedef  int /*<<< orphan*/  vinfo ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct bridge_vlan_info {scalar_t__ flags; scalar_t__ vid; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_VLAN_INFO_RANGE_BEGIN ; 
 scalar_t__ BRIDGE_VLAN_INFO_RANGE_END ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_BRIDGE_VLAN_INFO ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct bridge_vlan_info*) ; 

__attribute__((used)) static int br_fill_ifvlaninfo_range(struct sk_buff *skb, u16 vid_start,
				    u16 vid_end, u16 flags)
{
	struct  bridge_vlan_info vinfo;

	if ((vid_end - vid_start) > 0) {
		/* add range to skb */
		vinfo.vid = vid_start;
		vinfo.flags = flags | BRIDGE_VLAN_INFO_RANGE_BEGIN;
		if (nla_put(skb, IFLA_BRIDGE_VLAN_INFO,
			    sizeof(vinfo), &vinfo))
			goto nla_put_failure;

		vinfo.vid = vid_end;
		vinfo.flags = flags | BRIDGE_VLAN_INFO_RANGE_END;
		if (nla_put(skb, IFLA_BRIDGE_VLAN_INFO,
			    sizeof(vinfo), &vinfo))
			goto nla_put_failure;
	} else {
		vinfo.vid = vid_start;
		vinfo.flags = flags;
		if (nla_put(skb, IFLA_BRIDGE_VLAN_INFO,
			    sizeof(vinfo), &vinfo))
			goto nla_put_failure;
	}

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}