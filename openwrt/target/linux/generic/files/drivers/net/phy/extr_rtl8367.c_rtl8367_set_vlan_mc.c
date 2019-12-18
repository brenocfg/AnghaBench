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
struct rtl8366_vlan_mc {scalar_t__ vid; scalar_t__ priority; scalar_t__ member; scalar_t__ untag; scalar_t__ fid; } ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_WR (struct rtl8366_smi*,scalar_t__,scalar_t__) ; 
 scalar_t__ RTL8367_FIDMAX ; 
 scalar_t__ RTL8367_NUM_VIDS ; 
 scalar_t__ RTL8367_NUM_VLANS ; 
 scalar_t__ RTL8367_PRIORITYMAX ; 
 scalar_t__ RTL8367_UNTAG_MASK ; 
 scalar_t__ RTL8367_VLAN_MC_BASE (scalar_t__) ; 
 int RTL8367_VLAN_MC_DATA_SIZE ; 
 scalar_t__ RTL8367_VLAN_MC_EVID_MASK ; 
 scalar_t__ RTL8367_VLAN_MC_EVID_SHIFT ; 
 scalar_t__ RTL8367_VLAN_MC_FID_MASK ; 
 scalar_t__ RTL8367_VLAN_MC_FID_SHIFT ; 
 scalar_t__ RTL8367_VLAN_MC_MEMBER_MASK ; 
 scalar_t__ RTL8367_VLAN_MC_MEMBER_SHIFT ; 

__attribute__((used)) static int rtl8367_set_vlan_mc(struct rtl8366_smi *smi, u32 index,
				const struct rtl8366_vlan_mc *vlanmc)
{
	u32 data[RTL8367_VLAN_MC_DATA_SIZE];
	int err;
	int i;

	if (index >= RTL8367_NUM_VLANS ||
	    vlanmc->vid >= RTL8367_NUM_VIDS ||
	    vlanmc->priority > RTL8367_PRIORITYMAX ||
	    vlanmc->member > RTL8367_VLAN_MC_MEMBER_MASK ||
	    vlanmc->untag > RTL8367_UNTAG_MASK ||
	    vlanmc->fid > RTL8367_FIDMAX)
		return -EINVAL;

	data[0] = (vlanmc->member & RTL8367_VLAN_MC_MEMBER_MASK) <<
		  RTL8367_VLAN_MC_MEMBER_SHIFT;
	data[1] = (vlanmc->fid & RTL8367_VLAN_MC_FID_MASK) <<
		  RTL8367_VLAN_MC_FID_SHIFT;
	data[2] = 0;
	data[3] = (vlanmc->vid & RTL8367_VLAN_MC_EVID_MASK) <<
		   RTL8367_VLAN_MC_EVID_SHIFT;

	for (i = 0; i < ARRAY_SIZE(data); i++)
		REG_WR(smi, RTL8367_VLAN_MC_BASE(index) + i, data[i]);

	return 0;
}