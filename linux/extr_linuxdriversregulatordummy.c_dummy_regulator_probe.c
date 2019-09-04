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
struct regulator_config {int /*<<< orphan*/ * init_data; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_desc ; 
 int /*<<< orphan*/  dummy_initdata ; 
 int /*<<< orphan*/  dummy_regulator_rdev ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  regulator_register (int /*<<< orphan*/ *,struct regulator_config*) ; 

__attribute__((used)) static int dummy_regulator_probe(struct platform_device *pdev)
{
	struct regulator_config config = { };
	int ret;

	config.dev = &pdev->dev;
	config.init_data = &dummy_initdata;

	dummy_regulator_rdev = regulator_register(&dummy_desc, &config);
	if (IS_ERR(dummy_regulator_rdev)) {
		ret = PTR_ERR(dummy_regulator_rdev);
		pr_err("Failed to register regulator: %d\n", ret);
		return ret;
	}

	return 0;
}