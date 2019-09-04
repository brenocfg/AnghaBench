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
struct cmb_data {scalar_t__ last_update; int /*<<< orphan*/  size; int /*<<< orphan*/  hw_block; int /*<<< orphan*/  last_block; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmb_start_time; struct cmb_data* cmb; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmf_generic_reset(struct ccw_device *cdev)
{
	struct cmb_data *cmb_data;

	spin_lock_irq(cdev->ccwlock);
	cmb_data = cdev->private->cmb;
	if (cmb_data) {
		memset(cmb_data->last_block, 0, cmb_data->size);
		/*
		 * Need to reset hw block as well to make the hardware start
		 * from 0 again.
		 */
		memset(cmb_data->hw_block, 0, cmb_data->size);
		cmb_data->last_update = 0;
	}
	cdev->private->cmb_start_time = get_tod_clock();
	spin_unlock_irq(cdev->ccwlock);
}