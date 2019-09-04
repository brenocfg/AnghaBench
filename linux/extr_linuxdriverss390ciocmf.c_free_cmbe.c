#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cmb_data {int /*<<< orphan*/  hw_block; struct cmb_data* last_block; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmb_list; struct cmb_data* cmb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMF_OFF ; 
 TYPE_2__ cmb_area ; 
 int /*<<< orphan*/  cmbe_cache ; 
 int /*<<< orphan*/  cmf_activate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmb_data*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_cmbe(struct ccw_device *cdev)
{
	struct cmb_data *cmb_data;

	spin_lock(&cmb_area.lock);
	spin_lock_irq(cdev->ccwlock);
	cmb_data = cdev->private->cmb;
	cdev->private->cmb = NULL;
	if (cmb_data) {
		kfree(cmb_data->last_block);
		kmem_cache_free(cmbe_cache, cmb_data->hw_block);
	}
	kfree(cmb_data);

	/* deactivate global measurement if this is the last channel */
	list_del_init(&cdev->private->cmb_list);
	if (list_empty(&cmb_area.list))
		cmf_activate(NULL, CMF_OFF);
	spin_unlock_irq(cdev->ccwlock);
	spin_unlock(&cmb_area.lock);
}