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

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dgnc_board ; 
 int /*<<< orphan*/  dgnc_cleanup_board (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dgnc_cleanup_tty (int /*<<< orphan*/ ) ; 
 int dgnc_num_boards ; 
 int /*<<< orphan*/  dgnc_poll_lock ; 
 int dgnc_poll_stop ; 
 int /*<<< orphan*/  dgnc_poll_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cleanup(void)
{
	int i;
	unsigned long flags;

	spin_lock_irqsave(&dgnc_poll_lock, flags);
	dgnc_poll_stop = 1;
	spin_unlock_irqrestore(&dgnc_poll_lock, flags);

	/* Turn off poller right away. */
	del_timer_sync(&dgnc_poll_timer);

	for (i = 0; i < dgnc_num_boards; ++i) {
		dgnc_cleanup_tty(dgnc_board[i]);
		dgnc_cleanup_board(dgnc_board[i]);
	}
}