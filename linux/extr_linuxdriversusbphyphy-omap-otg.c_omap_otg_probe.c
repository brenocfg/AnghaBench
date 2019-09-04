#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {struct omap_usb_config* platform_data; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/ * resource; } ;
struct TYPE_7__ {int /*<<< orphan*/  notifier_call; } ;
struct otg_device {void* vbus; void* id; int /*<<< orphan*/  base; TYPE_4__ vbus_nb; TYPE_4__ id_nb; struct extcon_dev* extcon; } ;
struct omap_usb_config {int /*<<< orphan*/  extcon; } ;
struct extcon_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int,int,int /*<<< orphan*/ ,void*,void*) ; 
 int devm_extcon_register_notifier (TYPE_1__*,struct extcon_dev*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct otg_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct extcon_dev* extcon_get_extcon_dev (int /*<<< orphan*/ ) ; 
 void* extcon_get_state (struct extcon_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_otg_id_notifier ; 
 int /*<<< orphan*/  omap_otg_set_mode (struct otg_device*) ; 
 int /*<<< orphan*/  omap_otg_vbus_notifier ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct otg_device*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_otg_probe(struct platform_device *pdev)
{
	const struct omap_usb_config *config = pdev->dev.platform_data;
	struct otg_device *otg_dev;
	struct extcon_dev *extcon;
	int ret;
	u32 rev;

	if (!config || !config->extcon)
		return -ENODEV;

	extcon = extcon_get_extcon_dev(config->extcon);
	if (!extcon)
		return -EPROBE_DEFER;

	otg_dev = devm_kzalloc(&pdev->dev, sizeof(*otg_dev), GFP_KERNEL);
	if (!otg_dev)
		return -ENOMEM;

	otg_dev->base = devm_ioremap_resource(&pdev->dev, &pdev->resource[0]);
	if (IS_ERR(otg_dev->base))
		return PTR_ERR(otg_dev->base);

	otg_dev->extcon = extcon;
	otg_dev->id_nb.notifier_call = omap_otg_id_notifier;
	otg_dev->vbus_nb.notifier_call = omap_otg_vbus_notifier;

	ret = devm_extcon_register_notifier(&pdev->dev, extcon,
					EXTCON_USB_HOST, &otg_dev->id_nb);
	if (ret)
		return ret;

	ret = devm_extcon_register_notifier(&pdev->dev, extcon,
					EXTCON_USB, &otg_dev->vbus_nb);
	if (ret) {
		return ret;
	}

	otg_dev->id = extcon_get_state(extcon, EXTCON_USB_HOST);
	otg_dev->vbus = extcon_get_state(extcon, EXTCON_USB);
	omap_otg_set_mode(otg_dev);

	rev = readl(otg_dev->base);

	dev_info(&pdev->dev,
		 "OMAP USB OTG controller rev %d.%d (%s, id=%d, vbus=%d)\n",
		 (rev >> 4) & 0xf, rev & 0xf, config->extcon, otg_dev->id,
		 otg_dev->vbus);

	platform_set_drvdata(pdev, otg_dev);

	return 0;
}