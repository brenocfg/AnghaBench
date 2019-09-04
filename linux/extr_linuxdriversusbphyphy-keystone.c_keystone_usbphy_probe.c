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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  init; } ;
struct TYPE_3__ {TYPE_2__ phy; } ;
struct keystone_usbphy {TYPE_1__ usb_phy_gen; int /*<<< orphan*/  phy_ctrl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct keystone_usbphy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keystone_usbphy_init ; 
 int /*<<< orphan*/  keystone_usbphy_shutdown ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct keystone_usbphy*) ; 
 int usb_add_phy_dev (TYPE_2__*) ; 
 int usb_phy_gen_create_phy (struct device*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int keystone_usbphy_probe(struct platform_device *pdev)
{
	struct device		*dev = &pdev->dev;
	struct keystone_usbphy	*k_phy;
	struct resource		*res;
	int ret;

	k_phy = devm_kzalloc(dev, sizeof(*k_phy), GFP_KERNEL);
	if (!k_phy)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	k_phy->phy_ctrl = devm_ioremap_resource(dev, res);
	if (IS_ERR(k_phy->phy_ctrl))
		return PTR_ERR(k_phy->phy_ctrl);

	ret = usb_phy_gen_create_phy(dev, &k_phy->usb_phy_gen, NULL);
	if (ret)
		return ret;

	k_phy->usb_phy_gen.phy.init = keystone_usbphy_init;
	k_phy->usb_phy_gen.phy.shutdown = keystone_usbphy_shutdown;

	platform_set_drvdata(pdev, k_phy);

	return usb_add_phy_dev(&k_phy->usb_phy_gen.phy);
}