#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  i; } ;
struct switch_val {TYPE_1__ value; int /*<<< orphan*/  port_vlan; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int /*<<< orphan*/  max; } ;
struct rtl8366_vlan_4k {int /*<<< orphan*/  untag; int /*<<< orphan*/  member; } ;
struct rtl8366_smi {TYPE_2__* ops; } ;
struct TYPE_4__ {int (* get_vlan_4k ) (struct rtl8366_smi*,int /*<<< orphan*/ ,struct rtl8366_vlan_4k*) ;int /*<<< orphan*/  (* is_vlan_valid ) (struct rtl8366_smi*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int rtl8366_set_vlan (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rtl8366_smi*,int /*<<< orphan*/ ) ; 
 int stub2 (struct rtl8366_smi*,int /*<<< orphan*/ ,struct rtl8366_vlan_4k*) ; 
 struct rtl8366_smi* sw_to_rtl8366_smi (struct switch_dev*) ; 

int rtl8366_sw_set_vlan_fid(struct switch_dev *dev,
			    const struct switch_attr *attr,
			    struct switch_val *val)
{
	struct rtl8366_vlan_4k vlan4k;
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);
	int err;

	if (!smi->ops->is_vlan_valid(smi, val->port_vlan))
		return -EINVAL;

	if (val->value.i < 0 || val->value.i > attr->max)
		return -EINVAL;

	err = smi->ops->get_vlan_4k(smi, val->port_vlan, &vlan4k);
	if (err)
		return err;

	return rtl8366_set_vlan(smi, val->port_vlan,
				vlan4k.member,
				vlan4k.untag,
				val->value.i);
}