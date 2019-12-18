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
struct amixer_mgr {int /*<<< orphan*/  mgr_lock; int /*<<< orphan*/  mgr; TYPE_1__* card; } ;
struct amixer_desc {int msr; } ;
struct amixer {unsigned int* idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amixer_rsc_init (struct amixer*,struct amixer_desc const*,struct amixer_mgr*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct amixer*) ; 
 struct amixer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mgr_get_resource (int /*<<< orphan*/ *,int,unsigned int*) ; 
 int /*<<< orphan*/  mgr_put_resource (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int get_amixer_rsc(struct amixer_mgr *mgr,
			  const struct amixer_desc *desc,
			  struct amixer **ramixer)
{
	int err, i;
	unsigned int idx;
	struct amixer *amixer;
	unsigned long flags;

	*ramixer = NULL;

	/* Allocate mem for amixer resource */
	amixer = kzalloc(sizeof(*amixer), GFP_KERNEL);
	if (!amixer)
		return -ENOMEM;

	/* Check whether there are sufficient
	 * amixer resources to meet request. */
	err = 0;
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	for (i = 0; i < desc->msr; i++) {
		err = mgr_get_resource(&mgr->mgr, 1, &idx);
		if (err)
			break;

		amixer->idx[i] = idx;
	}
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	if (err) {
		dev_err(mgr->card->dev,
			"Can't meet AMIXER resource request!\n");
		goto error;
	}

	err = amixer_rsc_init(amixer, desc, mgr);
	if (err)
		goto error;

	*ramixer = amixer;

	return 0;

error:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	for (i--; i >= 0; i--)
		mgr_put_resource(&mgr->mgr, 1, amixer->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	kfree(amixer);
	return err;
}