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
struct TYPE_2__ {int /*<<< orphan*/  i; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int ofs; } ;
struct rtl8366_smi {int /*<<< orphan*/  vlan4k_enabled; int /*<<< orphan*/  vlan_enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rtl8366_smi* sw_to_rtl8366_smi (struct switch_dev*) ; 

int rtl8366_sw_get_vlan_enable(struct switch_dev *dev,
			       const struct switch_attr *attr,
			       struct switch_val *val)
{
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);

	if (attr->ofs > 2)
		return -EINVAL;

	if (attr->ofs == 1)
		val->value.i = smi->vlan_enabled;
	else
		val->value.i = smi->vlan4k_enabled;

	return 0;
}