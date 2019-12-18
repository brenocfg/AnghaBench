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
struct rtl8366_smi {scalar_t__ vlan4k_enabled; } ;

/* Variables and functions */
 int RTL8367_NUM_VIDS ; 
 unsigned int RTL8367_NUM_VLANS ; 

__attribute__((used)) static int rtl8367_is_vlan_valid(struct rtl8366_smi *smi, unsigned vlan)
{
	unsigned max = RTL8367_NUM_VLANS;

	if (smi->vlan4k_enabled)
		max = RTL8367_NUM_VIDS - 1;

	if (vlan == 0 || vlan >= max)
		return 0;

	return 1;
}