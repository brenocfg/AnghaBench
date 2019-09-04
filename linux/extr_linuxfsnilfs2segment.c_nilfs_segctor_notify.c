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
struct TYPE_2__ {int /*<<< orphan*/  expires; } ;
struct nilfs_sc_info {int sc_state; int /*<<< orphan*/  sc_state_lock; TYPE_1__ sc_timer; int /*<<< orphan*/  sc_flush_request; int /*<<< orphan*/  sc_seq_accepted; int /*<<< orphan*/  sc_seq_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_DAT_BIT ; 
 int /*<<< orphan*/  FLUSH_FILE_BIT ; 
 int NILFS_SEGCTOR_COMMIT ; 
 int SC_FLUSH_DAT ; 
 int SC_FLUSH_FILE ; 
 int SC_LSEG_SR ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nilfs_segctor_wakeup (struct nilfs_sc_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nilfs_segctor_notify(struct nilfs_sc_info *sci, int mode, int err)
{
	/* Clear requests (even when the construction failed) */
	spin_lock(&sci->sc_state_lock);

	if (mode == SC_LSEG_SR) {
		sci->sc_state &= ~NILFS_SEGCTOR_COMMIT;
		sci->sc_seq_done = sci->sc_seq_accepted;
		nilfs_segctor_wakeup(sci, err);
		sci->sc_flush_request = 0;
	} else {
		if (mode == SC_FLUSH_FILE)
			sci->sc_flush_request &= ~FLUSH_FILE_BIT;
		else if (mode == SC_FLUSH_DAT)
			sci->sc_flush_request &= ~FLUSH_DAT_BIT;

		/* re-enable timer if checkpoint creation was not done */
		if ((sci->sc_state & NILFS_SEGCTOR_COMMIT) &&
		    time_before(jiffies, sci->sc_timer.expires))
			add_timer(&sci->sc_timer);
	}
	spin_unlock(&sci->sc_state_lock);
}