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
typedef  scalar_t__ u32 ;
typedef  struct cmb* u16 ;
struct cmb_data {scalar_t__ hw_block; } ;
struct cmb {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_4__ {int mem; } ;
struct TYPE_3__ {struct cmb_data* cmb; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__ cmb_area ; 
 int set_schib_wait (struct ccw_device*,scalar_t__,int /*<<< orphan*/ ,struct cmb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int set_cmb(struct ccw_device *cdev, u32 mme)
{
	u16 offset;
	struct cmb_data *cmb_data;
	unsigned long flags;

	spin_lock_irqsave(cdev->ccwlock, flags);
	if (!cdev->private->cmb) {
		spin_unlock_irqrestore(cdev->ccwlock, flags);
		return -EINVAL;
	}
	cmb_data = cdev->private->cmb;
	offset = mme ? (struct cmb *)cmb_data->hw_block - cmb_area.mem : 0;
	spin_unlock_irqrestore(cdev->ccwlock, flags);

	return set_schib_wait(cdev, mme, 0, offset);
}