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
struct ar5523 {int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_nr_total; int /*<<< orphan*/  tx_flush_waitq; int /*<<< orphan*/  tx_wd_timer; int /*<<< orphan*/  tx_nr_pending; } ;

/* Variables and functions */
 scalar_t__ AR5523_TX_DATA_RESTART_COUNT ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ar5523_data_tx_pkt_put(struct ar5523 *ar)
{
	atomic_dec(&ar->tx_nr_total);
	if (!atomic_dec_return(&ar->tx_nr_pending)) {
		del_timer(&ar->tx_wd_timer);
		wake_up(&ar->tx_flush_waitq);
	}

	if (atomic_read(&ar->tx_nr_total) < AR5523_TX_DATA_RESTART_COUNT) {
		ar5523_dbg(ar, "restart tx queue\n");
		ieee80211_wake_queues(ar->hw);
	}
}