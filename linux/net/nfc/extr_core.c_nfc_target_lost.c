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
typedef  scalar_t__ u32 ;
struct nfc_target {scalar_t__ idx; } ;
struct nfc_dev {int n_targets; int /*<<< orphan*/  dev; struct nfc_target* targets; int /*<<< orphan*/ * active_target; int /*<<< orphan*/  targets_generation; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfc_target*) ; 
 int /*<<< orphan*/  memcpy (struct nfc_target*,struct nfc_target*,int) ; 
 int /*<<< orphan*/  nfc_genl_target_lost (struct nfc_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__) ; 

int nfc_target_lost(struct nfc_dev *dev, u32 target_idx)
{
	struct nfc_target *tg;
	int i;

	pr_debug("dev_name %s n_target %d\n", dev_name(&dev->dev), target_idx);

	device_lock(&dev->dev);

	for (i = 0; i < dev->n_targets; i++) {
		tg = &dev->targets[i];
		if (tg->idx == target_idx)
			break;
	}

	if (i == dev->n_targets) {
		device_unlock(&dev->dev);
		return -EINVAL;
	}

	dev->targets_generation++;
	dev->n_targets--;
	dev->active_target = NULL;

	if (dev->n_targets) {
		memcpy(&dev->targets[i], &dev->targets[i + 1],
		       (dev->n_targets - i) * sizeof(struct nfc_target));
	} else {
		kfree(dev->targets);
		dev->targets = NULL;
	}

	device_unlock(&dev->dev);

	nfc_genl_target_lost(dev, target_idx);

	return 0;
}