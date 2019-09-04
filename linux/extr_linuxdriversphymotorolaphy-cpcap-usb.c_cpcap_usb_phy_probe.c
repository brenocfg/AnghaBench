#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_otg {TYPE_1__* usb_phy; int /*<<< orphan*/  set_peripheral; int /*<<< orphan*/  set_host; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct phy_provider {int dummy; } ;
typedef  struct phy_provider phy ;
struct of_device_id {int dummy; } ;
struct TYPE_7__ {char* label; int /*<<< orphan*/  type; struct usb_otg* otg; TYPE_2__* dev; } ;
struct cpcap_phy_ddata {int /*<<< orphan*/  detect_work; int /*<<< orphan*/  active; TYPE_1__ phy; TYPE_2__* dev; struct phy_provider* vusb; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpcap_usb_detect ; 
 int cpcap_usb_init_iio (struct cpcap_phy_ddata*) ; 
 int cpcap_usb_init_interrupts (struct platform_device*,struct cpcap_phy_ddata*) ; 
 int /*<<< orphan*/  cpcap_usb_init_optional_gpios (struct cpcap_phy_ddata*) ; 
 int cpcap_usb_init_optional_pins (struct cpcap_phy_ddata*) ; 
 int /*<<< orphan*/  cpcap_usb_phy_id_table ; 
 int /*<<< orphan*/  cpcap_usb_phy_set_host ; 
 int /*<<< orphan*/  cpcap_usb_phy_set_peripheral ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct phy_provider* devm_regulator_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct cpcap_phy_ddata*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cpcap_phy_ddata*) ; 
 int regulator_enable (struct phy_provider*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_add_phy_dev (TYPE_1__*) ; 

__attribute__((used)) static int cpcap_usb_phy_probe(struct platform_device *pdev)
{
	struct cpcap_phy_ddata *ddata;
	struct phy *generic_phy;
	struct phy_provider *phy_provider;
	struct usb_otg *otg;
	const struct of_device_id *of_id;
	int error;

	of_id = of_match_device(of_match_ptr(cpcap_usb_phy_id_table),
				&pdev->dev);
	if (!of_id)
		return -EINVAL;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	ddata->reg = dev_get_regmap(pdev->dev.parent, NULL);
	if (!ddata->reg)
		return -ENODEV;

	otg = devm_kzalloc(&pdev->dev, sizeof(*otg), GFP_KERNEL);
	if (!otg)
		return -ENOMEM;

	ddata->dev = &pdev->dev;
	ddata->phy.dev = ddata->dev;
	ddata->phy.label = "cpcap_usb_phy";
	ddata->phy.otg = otg;
	ddata->phy.type = USB_PHY_TYPE_USB2;
	otg->set_host = cpcap_usb_phy_set_host;
	otg->set_peripheral = cpcap_usb_phy_set_peripheral;
	otg->usb_phy = &ddata->phy;
	INIT_DELAYED_WORK(&ddata->detect_work, cpcap_usb_detect);
	platform_set_drvdata(pdev, ddata);

	ddata->vusb = devm_regulator_get(&pdev->dev, "vusb");
	if (IS_ERR(ddata->vusb))
		return PTR_ERR(ddata->vusb);

	error = regulator_enable(ddata->vusb);
	if (error)
		return error;

	generic_phy = devm_phy_create(ddata->dev, NULL, &ops);
	if (IS_ERR(generic_phy)) {
		error = PTR_ERR(generic_phy);
		return PTR_ERR(generic_phy);
	}

	phy_set_drvdata(generic_phy, ddata);

	phy_provider = devm_of_phy_provider_register(ddata->dev,
						     of_phy_simple_xlate);
	if (IS_ERR(phy_provider))
		return PTR_ERR(phy_provider);

	error = cpcap_usb_init_optional_pins(ddata);
	if (error)
		return error;

	cpcap_usb_init_optional_gpios(ddata);

	error = cpcap_usb_init_iio(ddata);
	if (error)
		return error;

	error = cpcap_usb_init_interrupts(pdev, ddata);
	if (error)
		return error;

	usb_add_phy_dev(&ddata->phy);
	atomic_set(&ddata->active, 1);
	schedule_delayed_work(&ddata->detect_work, msecs_to_jiffies(1));

	return 0;
}