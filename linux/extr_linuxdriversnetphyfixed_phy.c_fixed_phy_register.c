#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_node* of_node; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;
struct phy_device {int speed; int is_pseudo_fixed_link; int /*<<< orphan*/  supported; TYPE_2__ mdio; int /*<<< orphan*/  asym_pause; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; scalar_t__ link; } ;
struct fixed_phy_status {int speed; int /*<<< orphan*/  asym_pause; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; scalar_t__ link; } ;
struct fixed_mdio_bus {TYPE_3__* mii_bus; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {scalar_t__ state; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 struct phy_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 scalar_t__ MDIOBUS_REGISTERED ; 
 int /*<<< orphan*/  PHY_1000BT_FEATURES ; 
 int /*<<< orphan*/  PHY_100BT_FEATURES ; 
 int /*<<< orphan*/  PHY_10BT_FEATURES ; 
 int /*<<< orphan*/  PHY_MAX_ADDR ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int fixed_phy_add (unsigned int,int,struct fixed_phy_status*,int) ; 
 int /*<<< orphan*/  fixed_phy_del (int) ; 
 struct phy_device* get_phy_device (TYPE_3__*,int,int) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  phy_device_free (struct phy_device*) ; 
 int phy_device_register (struct phy_device*) ; 
 int /*<<< orphan*/  phy_fixed_ida ; 
 struct fixed_mdio_bus platform_fmb ; 

struct phy_device *fixed_phy_register(unsigned int irq,
				      struct fixed_phy_status *status,
				      int link_gpio,
				      struct device_node *np)
{
	struct fixed_mdio_bus *fmb = &platform_fmb;
	struct phy_device *phy;
	int phy_addr;
	int ret;

	if (!fmb->mii_bus || fmb->mii_bus->state != MDIOBUS_REGISTERED)
		return ERR_PTR(-EPROBE_DEFER);

	/* Get the next available PHY address, up to PHY_MAX_ADDR */
	phy_addr = ida_simple_get(&phy_fixed_ida, 0, PHY_MAX_ADDR, GFP_KERNEL);
	if (phy_addr < 0)
		return ERR_PTR(phy_addr);

	ret = fixed_phy_add(irq, phy_addr, status, link_gpio);
	if (ret < 0) {
		ida_simple_remove(&phy_fixed_ida, phy_addr);
		return ERR_PTR(ret);
	}

	phy = get_phy_device(fmb->mii_bus, phy_addr, false);
	if (IS_ERR(phy)) {
		fixed_phy_del(phy_addr);
		return ERR_PTR(-EINVAL);
	}

	/* propagate the fixed link values to struct phy_device */
	phy->link = status->link;
	if (status->link) {
		phy->speed = status->speed;
		phy->duplex = status->duplex;
		phy->pause = status->pause;
		phy->asym_pause = status->asym_pause;
	}

	of_node_get(np);
	phy->mdio.dev.of_node = np;
	phy->is_pseudo_fixed_link = true;

	switch (status->speed) {
	case SPEED_1000:
		phy->supported = PHY_1000BT_FEATURES;
		break;
	case SPEED_100:
		phy->supported = PHY_100BT_FEATURES;
		break;
	case SPEED_10:
	default:
		phy->supported = PHY_10BT_FEATURES;
	}

	ret = phy_device_register(phy);
	if (ret) {
		phy_device_free(phy);
		of_node_put(np);
		fixed_phy_del(phy_addr);
		return ERR_PTR(ret);
	}

	return phy;
}