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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct extcon_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  notifier_call; } ;
struct dwc3_omap {struct extcon_dev* edev; TYPE_1__* dev; TYPE_3__ id_nb; TYPE_3__ vbus_nb; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 scalar_t__ IS_ERR (struct extcon_dev*) ; 
 int /*<<< orphan*/  OMAP_DWC3_ID_GROUND ; 
 int /*<<< orphan*/  OMAP_DWC3_VBUS_VALID ; 
 int /*<<< orphan*/  dev_vdbg (TYPE_1__*,char*) ; 
 int devm_extcon_register_notifier (TYPE_1__*,struct extcon_dev*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dwc3_omap_id_notifier ; 
 int /*<<< orphan*/  dwc3_omap_set_mailbox (struct dwc3_omap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_omap_vbus_notifier ; 
 struct extcon_dev* extcon_get_edev_by_phandle (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int extcon_get_state (struct extcon_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int dwc3_omap_extcon_register(struct dwc3_omap *omap)
{
	int			ret;
	struct device_node	*node = omap->dev->of_node;
	struct extcon_dev	*edev;

	if (of_property_read_bool(node, "extcon")) {
		edev = extcon_get_edev_by_phandle(omap->dev, 0);
		if (IS_ERR(edev)) {
			dev_vdbg(omap->dev, "couldn't get extcon device\n");
			return -EPROBE_DEFER;
		}

		omap->vbus_nb.notifier_call = dwc3_omap_vbus_notifier;
		ret = devm_extcon_register_notifier(omap->dev, edev,
						EXTCON_USB, &omap->vbus_nb);
		if (ret < 0)
			dev_vdbg(omap->dev, "failed to register notifier for USB\n");

		omap->id_nb.notifier_call = dwc3_omap_id_notifier;
		ret = devm_extcon_register_notifier(omap->dev, edev,
						EXTCON_USB_HOST, &omap->id_nb);
		if (ret < 0)
			dev_vdbg(omap->dev, "failed to register notifier for USB-HOST\n");

		if (extcon_get_state(edev, EXTCON_USB) == true)
			dwc3_omap_set_mailbox(omap, OMAP_DWC3_VBUS_VALID);
		if (extcon_get_state(edev, EXTCON_USB_HOST) == true)
			dwc3_omap_set_mailbox(omap, OMAP_DWC3_ID_GROUND);

		omap->edev = edev;
	}

	return 0;
}