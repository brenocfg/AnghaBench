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
typedef  int uint32_t ;
struct csio_hw {int flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int) ; 
 int CSIO_HWF_FWEVT_PENDING ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
csio_evtq_flush(struct csio_hw *hw)
{
	uint32_t count;
	count = 30;
	while (hw->flags & CSIO_HWF_FWEVT_PENDING && count--) {
		spin_unlock_irq(&hw->lock);
		msleep(2000);
		spin_lock_irq(&hw->lock);
	}

	CSIO_DB_ASSERT(!(hw->flags & CSIO_HWF_FWEVT_PENDING));
}