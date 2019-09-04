#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator_init_data {int dummy; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db8500_regulator_matches ; 
 int db8500_regulator_of_probe (struct platform_device*,struct device_node*) ; 
 int db8500_regulator_register (struct platform_device*,struct regulator_init_data*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbx500_regulator_info ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct regulator_init_data* dev_get_platdata (TYPE_1__*) ; 
 int of_regulator_match (TYPE_1__*,struct device_node*,int /*<<< orphan*/ ,int) ; 
 int ux500_regulator_debug_init (struct platform_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int db8500_regulator_probe(struct platform_device *pdev)
{
	struct regulator_init_data *db8500_init_data =
					dev_get_platdata(&pdev->dev);
	struct device_node *np = pdev->dev.of_node;
	int i, err;

	/* register all regulators */
	if (np) {
		err = of_regulator_match(&pdev->dev, np,
					db8500_regulator_matches,
					ARRAY_SIZE(db8500_regulator_matches));
		if (err < 0) {
			dev_err(&pdev->dev,
				"Error parsing regulator init data: %d\n", err);
			return err;
		}

		err = db8500_regulator_of_probe(pdev, np);
		if (err)
			return err;
	} else {
		for (i = 0; i < ARRAY_SIZE(dbx500_regulator_info); i++) {
			err = db8500_regulator_register(pdev,
							&db8500_init_data[i],
							i, NULL);
			if (err)
				return err;
		}
	}

	err = ux500_regulator_debug_init(pdev,
					 dbx500_regulator_info,
					 ARRAY_SIZE(dbx500_regulator_info));
	return 0;
}