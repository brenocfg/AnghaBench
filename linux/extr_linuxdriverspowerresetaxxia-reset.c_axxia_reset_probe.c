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
struct device {TYPE_1__* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axxia_restart_nb ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int register_restart_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (TYPE_1__*,char*) ; 

__attribute__((used)) static int axxia_reset_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int err;

	syscon = syscon_regmap_lookup_by_phandle(dev->of_node, "syscon");
	if (IS_ERR(syscon)) {
		pr_err("%s: syscon lookup failed\n", dev->of_node->name);
		return PTR_ERR(syscon);
	}

	err = register_restart_handler(&axxia_restart_nb);
	if (err)
		dev_err(dev, "cannot register restart handler (err=%d)\n", err);

	return err;
}