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
struct gbe_intf {int /*<<< orphan*/  dev; struct gbe_intf* slave; int /*<<< orphan*/  gbe_intf_list; TYPE_1__* ndev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ethtool_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct gbe_intf*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gbe_release(void *intf_priv)
{
	struct gbe_intf *gbe_intf = intf_priv;

	gbe_intf->ndev->ethtool_ops = NULL;
	list_del(&gbe_intf->gbe_intf_list);
	devm_kfree(gbe_intf->dev, gbe_intf->slave);
	devm_kfree(gbe_intf->dev, gbe_intf);
	return 0;
}