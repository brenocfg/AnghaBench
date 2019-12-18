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
struct src_mgr {int /*<<< orphan*/  mgr_lock; int /*<<< orphan*/  mgr; TYPE_1__* card; } ;
struct src_desc {scalar_t__ mode; int multi; } ;
struct src {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MEMRD ; 
 unsigned int SRC_RESOURCE_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct src* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct src*) ; 
 struct src* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mgr_get_resource (int /*<<< orphan*/ *,int,unsigned int*) ; 
 int /*<<< orphan*/  mgr_put_resource (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int src_rsc_init (struct src*,unsigned int,struct src_desc const*,struct src_mgr*) ; 

__attribute__((used)) static int
get_src_rsc(struct src_mgr *mgr, const struct src_desc *desc, struct src **rsrc)
{
	unsigned int idx = SRC_RESOURCE_NUM;
	int err;
	struct src *src;
	unsigned long flags;

	*rsrc = NULL;

	/* Check whether there are sufficient src resources to meet request. */
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	if (MEMRD == desc->mode)
		err = mgr_get_resource(&mgr->mgr, desc->multi, &idx);
	else
		err = mgr_get_resource(&mgr->mgr, 1, &idx);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	if (err) {
		dev_err(mgr->card->dev,
			"Can't meet SRC resource request!\n");
		return err;
	}

	/* Allocate mem for master src resource */
	if (MEMRD == desc->mode)
		src = kcalloc(desc->multi, sizeof(*src), GFP_KERNEL);
	else
		src = kzalloc(sizeof(*src), GFP_KERNEL);

	if (!src) {
		err = -ENOMEM;
		goto error1;
	}

	err = src_rsc_init(src, idx, desc, mgr);
	if (err)
		goto error2;

	*rsrc = src;

	return 0;

error2:
	kfree(src);
error1:
	spin_lock_irqsave(&mgr->mgr_lock, flags);
	if (MEMRD == desc->mode)
		mgr_put_resource(&mgr->mgr, desc->multi, idx);
	else
		mgr_put_resource(&mgr->mgr, 1, idx);

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	return err;
}