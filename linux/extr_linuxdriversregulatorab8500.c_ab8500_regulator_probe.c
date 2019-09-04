#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct device_node* of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_regulator_match {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; } ;
struct device_node {int dummy; } ;
struct ab8500 {int dummy; } ;
struct TYPE_5__ {int info_size; struct of_regulator_match* match; int /*<<< orphan*/  match_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ab8500_regulator_register (struct platform_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abx500_get_regulator_info (struct ab8500*) ; 
 TYPE_3__ abx500_regulator ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct ab8500* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int of_regulator_match (TYPE_1__*,struct device_node*,struct of_regulator_match*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_regulator_probe(struct platform_device *pdev)
{
	struct ab8500 *ab8500 = dev_get_drvdata(pdev->dev.parent);
	struct device_node *np = pdev->dev.of_node;
	struct of_regulator_match *match;
	int err, i;

	if (!ab8500) {
		dev_err(&pdev->dev, "null mfd parent\n");
		return -EINVAL;
	}

	abx500_get_regulator_info(ab8500);

	err = of_regulator_match(&pdev->dev, np,
				 abx500_regulator.match,
				 abx500_regulator.match_size);
	if (err < 0) {
		dev_err(&pdev->dev,
			"Error parsing regulator init data: %d\n", err);
		return err;
	}

	match = abx500_regulator.match;
	for (i = 0; i < abx500_regulator.info_size; i++) {
		err = ab8500_regulator_register(pdev, match[i].init_data, i,
						match[i].of_node);
		if (err)
			return err;
	}

	return 0;
}