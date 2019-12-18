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
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_RD (struct rtl8366_smi*,int /*<<< orphan*/ ,int*) ; 
 int RTL8367B_NUM_PORTS ; 
 int RTL8367B_VLAN_PVID_CTRL_MASK ; 
 int /*<<< orphan*/  RTL8367B_VLAN_PVID_CTRL_REG (int) ; 
 int RTL8367B_VLAN_PVID_CTRL_SHIFT (int) ; 

__attribute__((used)) static int rtl8367b_get_mc_index(struct rtl8366_smi *smi, int port, int *val)
{
	u32 data;
	int err;

	if (port >= RTL8367B_NUM_PORTS)
		return -EINVAL;

	REG_RD(smi, RTL8367B_VLAN_PVID_CTRL_REG(port), &data);

	*val = (data >> RTL8367B_VLAN_PVID_CTRL_SHIFT(port)) &
	       RTL8367B_VLAN_PVID_CTRL_MASK;

	return 0;
}