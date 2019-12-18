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
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8367_VLAN_CTRL_ENABLE ; 
 int /*<<< orphan*/  RTL8367_VLAN_CTRL_REG ; 
 int rtl8366_smi_rmwr (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8367_enable_vlan(struct rtl8366_smi *smi, int enable)
{
	return rtl8366_smi_rmwr(smi, RTL8367_VLAN_CTRL_REG,
				RTL8367_VLAN_CTRL_ENABLE,
				(enable) ? RTL8367_VLAN_CTRL_ENABLE : 0);
}