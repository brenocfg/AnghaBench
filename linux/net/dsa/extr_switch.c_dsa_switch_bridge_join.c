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
struct dsa_switch {scalar_t__ index; TYPE_1__* ops; } ;
struct dsa_notifier_bridge_info {scalar_t__ sw_index; int /*<<< orphan*/  br; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int (* port_bridge_join ) (struct dsa_switch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* crosschip_bridge_join ) (struct dsa_switch*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct dsa_switch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct dsa_switch*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_switch_bridge_join(struct dsa_switch *ds,
				  struct dsa_notifier_bridge_info *info)
{
	if (ds->index == info->sw_index && ds->ops->port_bridge_join)
		return ds->ops->port_bridge_join(ds, info->port, info->br);

	if (ds->index != info->sw_index && ds->ops->crosschip_bridge_join)
		return ds->ops->crosschip_bridge_join(ds, info->sw_index,
						      info->port, info->br);

	return 0;
}