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
struct timer_list {int dummy; } ;
struct csio_mbm {struct csio_hw* hw; } ;
struct csio_mb {int /*<<< orphan*/  (* mb_cbfn ) (struct csio_hw*,struct csio_mb*) ;} ;
struct csio_hw {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct csio_mb* csio_mb_tmo_handler (struct csio_hw*) ; 
 struct csio_mbm* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct csio_mbm* mbm ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void
csio_hw_mb_timer(struct timer_list *t)
{
	struct csio_mbm *mbm = from_timer(mbm, t, timer);
	struct csio_hw *hw = mbm->hw;
	struct csio_mb *mbp = NULL;

	spin_lock_irq(&hw->lock);
	mbp = csio_mb_tmo_handler(hw);
	spin_unlock_irq(&hw->lock);

	/* Call back the function for the timed-out Mailbox */
	if (mbp)
		mbp->mb_cbfn(hw, mbp);

}