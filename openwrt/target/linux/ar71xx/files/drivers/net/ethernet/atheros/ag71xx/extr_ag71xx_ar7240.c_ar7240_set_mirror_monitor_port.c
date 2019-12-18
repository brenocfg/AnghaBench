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
struct TYPE_2__ {int i; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct mii_bus {int dummy; } ;
struct ar7240sw {struct mii_bus* mii_bus; } ;

/* Variables and functions */
 int AR7240_MIRROR_PORT_M ; 
 int AR7240_MIRROR_PORT_S ; 
 int /*<<< orphan*/  AR7240_REG_CPU_PORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  ar7240sw_reg_rmw (struct mii_bus*,int /*<<< orphan*/ ,int,int) ; 
 struct ar7240sw* sw_to_ar7240 (struct switch_dev*) ; 

__attribute__((used)) static int
ar7240_set_mirror_monitor_port(struct switch_dev *dev,
				const struct switch_attr *attr,
				struct switch_val *val)
{
	struct ar7240sw *as = sw_to_ar7240(dev);
	struct mii_bus *mii = as->mii_bus;

	int port = val->value.i;

	if (port > 15)
		return -EINVAL;

	ar7240sw_reg_rmw(mii, AR7240_REG_CPU_PORT,
		AR7240_MIRROR_PORT_M << AR7240_MIRROR_PORT_S,
		port << AR7240_MIRROR_PORT_S);

	return 0;
}