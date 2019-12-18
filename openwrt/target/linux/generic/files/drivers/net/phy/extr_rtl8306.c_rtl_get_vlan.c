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
struct switch_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL_REG_VLAN_ENABLE ; 
 int /*<<< orphan*/  rtl_get (struct switch_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtl_get_vlan(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	val->value.i = rtl_get(dev, RTL_REG_VLAN_ENABLE);
	return 0;
}