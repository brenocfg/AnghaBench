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
struct srcimp_mgr {int /*<<< orphan*/  mgr_lock; int /*<<< orphan*/  mgr; TYPE_1__* card; } ;
struct srcimp_desc {int msr; } ;
struct srcimp {unsigned int* idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct srcimp*) ; 
 struct srcimp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mgr_get_resource (int /*<<< orphan*/ *,int,unsigned int*) ; 
 int /*<<< orphan*/  mgr_put_resource (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int srcimp_rsc_init (struct srcimp*,struct srcimp_desc const*,struct srcimp_mgr*) ; 

__attribute__((used)) static int get_srcimp_rsc(struct srcimp_mgr *mgr,
			  const struct srcimp_desc *desc,
			  struct srcimp **rsrcimp)
{
	int err, i;
	unsigned int idx;
	struct srcimp *srcimp;
	unsigned long flags;

	*rsrcimp = NULL;

	/* Allocate mem for SRCIMP resource */
	srcimp = kzalloc(sizeof(*srcimp), GFP_KERNEL);
	if (!srcimp)
		return -ENOMEM;

	/* Check whether there are sufficient SRCIMP resources. */
	err = 0;
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	for (i = 0; i < desc->msr; i++) {
		err = mgr_get_resource(&mgr->mgr, 1, &idx);
		if (err)
			break;

		srcimp->idx[i] = idx;
	}
	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	if (err) {
		dev_err(mgr->card->dev,
			"Can't meet SRCIMP resource request!\n");
		goto error1;
	}

	err = srcimp_rsc_init(srcimp, desc, mgr);
	if (err)
		goto error1;

	*rsrcimp = srcimp;

	return 0;

error1:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	for (i--; i >= 0; i--)
		mgr_put_resource(&mgr->mgr, 1, srcimp->idx[i]);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	kfree(srcimp);
	return err;
}