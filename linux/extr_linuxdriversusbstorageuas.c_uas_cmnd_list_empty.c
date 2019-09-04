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
struct uas_dev_info {int qdepth; int /*<<< orphan*/  lock; scalar_t__* cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int uas_cmnd_list_empty(struct uas_dev_info *devinfo)
{
	unsigned long flags;
	int i, r = 1;

	spin_lock_irqsave(&devinfo->lock, flags);

	for (i = 0; i < devinfo->qdepth; i++) {
		if (devinfo->cmnd[i]) {
			r = 0; /* Not empty */
			break;
		}
	}

	spin_unlock_irqrestore(&devinfo->lock, flags);

	return r;
}