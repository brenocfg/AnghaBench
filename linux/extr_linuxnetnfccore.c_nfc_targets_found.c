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
struct nfc_target {scalar_t__ idx; } ;
struct nfc_dev {int polling; int n_targets; int /*<<< orphan*/  dev; int /*<<< orphan*/ * targets; int /*<<< orphan*/  targets_generation; int /*<<< orphan*/  target_next_idx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (struct nfc_target*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_genl_targets_found (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

int nfc_targets_found(struct nfc_dev *dev,
		      struct nfc_target *targets, int n_targets)
{
	int i;

	pr_debug("dev_name=%s n_targets=%d\n", dev_name(&dev->dev), n_targets);

	for (i = 0; i < n_targets; i++)
		targets[i].idx = dev->target_next_idx++;

	device_lock(&dev->dev);

	if (dev->polling == false) {
		device_unlock(&dev->dev);
		return 0;
	}

	dev->polling = false;

	dev->targets_generation++;

	kfree(dev->targets);
	dev->targets = NULL;

	if (targets) {
		dev->targets = kmemdup(targets,
				       n_targets * sizeof(struct nfc_target),
				       GFP_ATOMIC);

		if (!dev->targets) {
			dev->n_targets = 0;
			device_unlock(&dev->dev);
			return -ENOMEM;
		}
	}

	dev->n_targets = n_targets;
	device_unlock(&dev->dev);

	nfc_genl_targets_found(dev);

	return 0;
}