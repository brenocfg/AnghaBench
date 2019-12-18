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
struct rtl8366_smi {int vlan_enabled; TYPE_1__* ops; scalar_t__ vlan4k_enabled; } ;
struct TYPE_2__ {int (* enable_vlan ) (struct rtl8366_smi*,int) ;int (* enable_vlan4k ) (struct rtl8366_smi*,int) ;} ;

/* Variables and functions */
 int stub1 (struct rtl8366_smi*,int) ; 
 int stub2 (struct rtl8366_smi*,int) ; 

int rtl8366_enable_vlan(struct rtl8366_smi *smi, int enable)
{
	int err;

	err = smi->ops->enable_vlan(smi, enable);
	if (err)
		return err;

	smi->vlan_enabled = enable;

	if (!enable) {
		smi->vlan4k_enabled = 0;
		err = smi->ops->enable_vlan4k(smi, enable);
	}

	return err;
}