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
struct regmap {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_resets; int /*<<< orphan*/ * ops; struct device_node* of_node; } ;
struct hi6220_reset_data {TYPE_1__ rc_dev; struct regmap* regmap; } ;
struct device_node {int dummy; } ;
typedef  enum hi6220_reset_ctrl_type { ____Placeholder_hi6220_reset_ctrl_type } hi6220_reset_ctrl_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int MEDIA ; 
 int /*<<< orphan*/  MEDIA_MAX_INDEX ; 
 int /*<<< orphan*/  PERIPH_MAX_INDEX ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct hi6220_reset_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6220_media_reset_ops ; 
 int /*<<< orphan*/  hi6220_peripheral_reset_ops ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int reset_controller_register (TYPE_1__*) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int hi6220_reset_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	enum hi6220_reset_ctrl_type type;
	struct hi6220_reset_data *data;
	struct regmap *regmap;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	type = (enum hi6220_reset_ctrl_type)of_device_get_match_data(dev);

	regmap = syscon_node_to_regmap(np);
	if (IS_ERR(regmap)) {
		dev_err(dev, "failed to get reset controller regmap\n");
		return PTR_ERR(regmap);
	}

	data->regmap = regmap;
	data->rc_dev.of_node = np;
	if (type == MEDIA) {
		data->rc_dev.ops = &hi6220_media_reset_ops;
		data->rc_dev.nr_resets = MEDIA_MAX_INDEX;
	} else {
		data->rc_dev.ops = &hi6220_peripheral_reset_ops;
		data->rc_dev.nr_resets = PERIPH_MAX_INDEX;
	}

	return reset_controller_register(&data->rc_dev);
}