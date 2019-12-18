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
struct wcd9335_codec {void* if_regmap; struct slim_device* slim_ifc_dev; void* regmap; struct slim_device* slim; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct slim_device {int /*<<< orphan*/  ctrl; struct device dev; } ;
struct device_node {int dummy; } ;
typedef  enum slim_device_status { ____Placeholder_slim_device_status } slim_device_status ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct wcd9335_codec* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct slim_device* of_slim_get_device (int /*<<< orphan*/ ,struct device_node*) ; 
 void* regmap_init_slimbus (struct slim_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slim_get_logical_addr (struct slim_device*) ; 
 int wcd9335_bring_up (struct wcd9335_codec*) ; 
 int /*<<< orphan*/  wcd9335_ifc_regmap_config ; 
 int wcd9335_irq_init (struct wcd9335_codec*) ; 
 int /*<<< orphan*/  wcd9335_probe (struct wcd9335_codec*) ; 
 int /*<<< orphan*/  wcd9335_regmap_config ; 

__attribute__((used)) static int wcd9335_slim_status(struct slim_device *sdev,
			       enum slim_device_status status)
{
	struct device *dev = &sdev->dev;
	struct device_node *ifc_dev_np;
	struct wcd9335_codec *wcd;
	int ret;

	wcd = dev_get_drvdata(dev);

	ifc_dev_np = of_parse_phandle(dev->of_node, "slim-ifc-dev", 0);
	if (!ifc_dev_np) {
		dev_err(dev, "No Interface device found\n");
		return -EINVAL;
	}

	wcd->slim = sdev;
	wcd->slim_ifc_dev = of_slim_get_device(sdev->ctrl, ifc_dev_np);
	of_node_put(ifc_dev_np);
	if (!wcd->slim_ifc_dev) {
		dev_err(dev, "Unable to get SLIM Interface device\n");
		return -EINVAL;
	}

	slim_get_logical_addr(wcd->slim_ifc_dev);

	wcd->regmap = regmap_init_slimbus(sdev, &wcd9335_regmap_config);
	if (IS_ERR(wcd->regmap)) {
		dev_err(dev, "Failed to allocate slim register map\n");
		return PTR_ERR(wcd->regmap);
	}

	wcd->if_regmap = regmap_init_slimbus(wcd->slim_ifc_dev,
						  &wcd9335_ifc_regmap_config);
	if (IS_ERR(wcd->if_regmap)) {
		dev_err(dev, "Failed to allocate ifc register map\n");
		return PTR_ERR(wcd->if_regmap);
	}

	ret = wcd9335_bring_up(wcd);
	if (ret) {
		dev_err(dev, "Failed to bringup WCD9335\n");
		return ret;
	}

	ret = wcd9335_irq_init(wcd);
	if (ret)
		return ret;

	wcd9335_probe(wcd);

	return ret;
}