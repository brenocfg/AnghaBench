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
struct usb_phy_roothub {int /*<<< orphan*/  list; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_GENERIC_PHY ; 
 int ENOMEM ; 
 struct usb_phy_roothub* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct usb_phy_roothub* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int of_count_phandle_with_args (int /*<<< orphan*/ ,char*,char*) ; 
 int usb_phy_roothub_add_phy (struct device*,int,int /*<<< orphan*/ *) ; 

struct usb_phy_roothub *usb_phy_roothub_alloc(struct device *dev)
{
	struct usb_phy_roothub *phy_roothub;
	int i, num_phys, err;

	if (!IS_ENABLED(CONFIG_GENERIC_PHY))
		return NULL;

	num_phys = of_count_phandle_with_args(dev->of_node, "phys",
					      "#phy-cells");
	if (num_phys <= 0)
		return NULL;

	phy_roothub = devm_kzalloc(dev, sizeof(*phy_roothub), GFP_KERNEL);
	if (!phy_roothub)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&phy_roothub->list);

	for (i = 0; i < num_phys; i++) {
		err = usb_phy_roothub_add_phy(dev, i, &phy_roothub->list);
		if (err)
			return ERR_PTR(err);
	}

	return phy_roothub;
}