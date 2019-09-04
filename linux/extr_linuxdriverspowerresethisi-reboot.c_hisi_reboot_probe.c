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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  hisi_restart_nb ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  reboot_offset ; 
 int register_restart_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_reboot_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	int err;

	base = of_iomap(np, 0);
	if (!base) {
		WARN(1, "failed to map base address");
		return -ENODEV;
	}

	if (of_property_read_u32(np, "reboot-offset", &reboot_offset) < 0) {
		pr_err("failed to find reboot-offset property\n");
		iounmap(base);
		return -EINVAL;
	}

	err = register_restart_handler(&hisi_restart_nb);
	if (err) {
		dev_err(&pdev->dev, "cannot register restart handler (err=%d)\n",
			err);
		iounmap(base);
	}

	return err;
}