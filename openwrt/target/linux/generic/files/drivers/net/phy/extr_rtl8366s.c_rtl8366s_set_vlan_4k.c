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
typedef  int u32 ;
struct rtl8366_vlan_4k {int vid; int member; int untag; int fid; } ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTL8366S_FIDMAX ; 
 int RTL8366S_NUM_VIDS ; 
 scalar_t__ RTL8366S_TABLE_ACCESS_CTRL_REG ; 
 int RTL8366S_TABLE_VLAN_WRITE_CTRL ; 
 int RTL8366S_VLAN_FID_MASK ; 
 int RTL8366S_VLAN_FID_SHIFT ; 
 int RTL8366S_VLAN_MEMBER_MASK ; 
 scalar_t__ RTL8366S_VLAN_TABLE_WRITE_BASE ; 
 int RTL8366S_VLAN_UNTAG_MASK ; 
 int RTL8366S_VLAN_UNTAG_SHIFT ; 
 int RTL8366S_VLAN_VID_MASK ; 
 int rtl8366_smi_write_reg (struct rtl8366_smi*,scalar_t__,int) ; 

__attribute__((used)) static int rtl8366s_set_vlan_4k(struct rtl8366_smi *smi,
				const struct rtl8366_vlan_4k *vlan4k)
{
	u32 data[2];
	int err;
	int i;

	if (vlan4k->vid >= RTL8366S_NUM_VIDS ||
	    vlan4k->member > RTL8366S_VLAN_MEMBER_MASK ||
	    vlan4k->untag > RTL8366S_VLAN_UNTAG_MASK ||
	    vlan4k->fid > RTL8366S_FIDMAX)
		return -EINVAL;

	data[0] = vlan4k->vid & RTL8366S_VLAN_VID_MASK;
	data[1] = (vlan4k->member & RTL8366S_VLAN_MEMBER_MASK) |
		  ((vlan4k->untag & RTL8366S_VLAN_UNTAG_MASK) <<
			RTL8366S_VLAN_UNTAG_SHIFT) |
		  ((vlan4k->fid & RTL8366S_VLAN_FID_MASK) <<
			RTL8366S_VLAN_FID_SHIFT);

	for (i = 0; i < 2; i++) {
		err = rtl8366_smi_write_reg(smi,
					    RTL8366S_VLAN_TABLE_WRITE_BASE + i,
					    data[i]);
		if (err)
			return err;
	}

	/* write table access control word */
	err = rtl8366_smi_write_reg(smi, RTL8366S_TABLE_ACCESS_CTRL_REG,
				    RTL8366S_TABLE_VLAN_WRITE_CTRL);

	return err;
}