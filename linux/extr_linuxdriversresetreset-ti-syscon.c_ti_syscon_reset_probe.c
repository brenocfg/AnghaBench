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
struct TYPE_2__ {int nr_resets; struct device_node* of_node; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;
struct ti_syscon_reset_data {int nr_controls; TYPE_1__ rcdev; struct ti_syscon_reset_control* controls; struct regmap* regmap; } ;
struct ti_syscon_reset_control {void* flags; void* status_bit; void* status_offset; void* deassert_bit; void* deassert_offset; void* assert_bit; void* assert_offset; } ;
struct regmap {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 void* be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct ti_syscon_reset_control* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct ti_syscon_reset_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ti_syscon_reset_data*) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_syscon_reset_ops ; 

__attribute__((used)) static int ti_syscon_reset_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct ti_syscon_reset_data *data;
	struct regmap *regmap;
	const __be32 *list;
	struct ti_syscon_reset_control *controls;
	int size, nr_controls, i;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	regmap = syscon_node_to_regmap(np->parent);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	list = of_get_property(np, "ti,reset-bits", &size);
	if (!list || (size / sizeof(*list)) % 7 != 0) {
		dev_err(dev, "invalid DT reset description\n");
		return -EINVAL;
	}

	nr_controls = (size / sizeof(*list)) / 7;
	controls = devm_kcalloc(dev, nr_controls, sizeof(*controls),
				GFP_KERNEL);
	if (!controls)
		return -ENOMEM;

	for (i = 0; i < nr_controls; i++) {
		controls[i].assert_offset = be32_to_cpup(list++);
		controls[i].assert_bit = be32_to_cpup(list++);
		controls[i].deassert_offset = be32_to_cpup(list++);
		controls[i].deassert_bit = be32_to_cpup(list++);
		controls[i].status_offset = be32_to_cpup(list++);
		controls[i].status_bit = be32_to_cpup(list++);
		controls[i].flags = be32_to_cpup(list++);
	}

	data->rcdev.ops = &ti_syscon_reset_ops;
	data->rcdev.owner = THIS_MODULE;
	data->rcdev.of_node = np;
	data->rcdev.nr_resets = nr_controls;
	data->regmap = regmap;
	data->controls = controls;
	data->nr_controls = nr_controls;

	platform_set_drvdata(pdev, data);

	return devm_reset_controller_register(dev, &data->rcdev);
}