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
struct pnp_dev {int num_dependent_sets; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pnp_assign_resources (struct pnp_dev*,int) ; 
 int /*<<< orphan*/  pnp_can_configure (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*) ; 

int pnp_auto_config_dev(struct pnp_dev *dev)
{
	int i, ret;

	if (!pnp_can_configure(dev)) {
		pnp_dbg(&dev->dev, "configuration not supported\n");
		return -ENODEV;
	}

	ret = pnp_assign_resources(dev, 0);
	if (ret == 0)
		return 0;

	for (i = 1; i < dev->num_dependent_sets; i++) {
		ret = pnp_assign_resources(dev, i);
		if (ret == 0)
			return 0;
	}

	dev_err(&dev->dev, "unable to assign resources\n");
	return ret;
}