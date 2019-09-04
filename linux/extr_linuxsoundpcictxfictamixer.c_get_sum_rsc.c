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
struct sum_mgr {int /*<<< orphan*/  mgr_lock; int /*<<< orphan*/  mgr; TYPE_1__* card; } ;
struct sum_desc {int msr; } ;
struct sum {unsigned int* idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct sum*) ; 
 struct sum* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mgr_get_resource (int /*<<< orphan*/ *,int,unsigned int*) ; 
 int /*<<< orphan*/  mgr_put_resource (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sum_rsc_init (struct sum*,struct sum_desc const*,struct sum_mgr*) ; 

__attribute__((used)) static int get_sum_rsc(struct sum_mgr *mgr,
		       const struct sum_desc *desc,
		       struct sum **rsum)
{
	int err, i;
	unsigned int idx;
	struct sum *sum;
	unsigned long flags;

	*rsum = NULL;

	/* Allocate mem for sum resource */
	sum = kzalloc(sizeof(*sum), GFP_KERNEL);
	if (!sum)
		return -ENOMEM;

	/* Check whether there are sufficient sum resources to meet request. */
	err = 0;
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	for (i = 0; i < desc->msr; i++) {
		err = mgr_get_resource(&mgr->mgr, 1, &idx);
		if (err)
			break;

		sum->idx[i] = idx;
	}
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	if (err) {
		dev_err(mgr->card->dev,
			"Can't meet SUM resource request!\n");
		goto error;
	}

	err = sum_rsc_init(sum, desc, mgr);
	if (err)
		goto error;

	*rsum = sum;

	return 0;

error:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	for (i--; i >= 0; i--)
		mgr_put_resource(&mgr->mgr, 1, sum->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	kfree(sum);
	return err;
}