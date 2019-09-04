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
struct cw1200_common {int bh_error; int /*<<< orphan*/  bh_wq; int /*<<< orphan*/  hw_bufs_used; TYPE_1__* hw; int /*<<< orphan*/  bh_evt_wq; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/  tx_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long WSM_CMD_LAST_CHANCE_TIMEOUT ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int cw1200_queue_get_xmit_timestamp (int /*<<< orphan*/ *,unsigned long*,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

bool wsm_flush_tx(struct cw1200_common *priv)
{
	unsigned long timestamp = jiffies;
	bool pending = false;
	long timeout;
	int i;

	/* Flush must be called with TX lock held. */
	BUG_ON(!atomic_read(&priv->tx_lock));

	/* First check if we really need to do something.
	 * It is safe to use unprotected access, as hw_bufs_used
	 * can only decrements.
	 */
	if (!priv->hw_bufs_used)
		return true;

	if (priv->bh_error) {
		/* In case of failure do not wait for magic. */
		pr_err("[WSM] Fatal error occurred, will not flush TX.\n");
		return false;
	} else {
		/* Get a timestamp of "oldest" frame */
		for (i = 0; i < 4; ++i)
			pending |= cw1200_queue_get_xmit_timestamp(
					&priv->tx_queue[i],
					&timestamp, 0xffffffff);
		/* If there's nothing pending, we're good */
		if (!pending)
			return true;

		timeout = timestamp + WSM_CMD_LAST_CHANCE_TIMEOUT - jiffies;
		if (timeout < 0 || wait_event_timeout(priv->bh_evt_wq,
						      !priv->hw_bufs_used,
						      timeout) <= 0) {
			/* Hmmm... Not good. Frame had stuck in firmware. */
			priv->bh_error = 1;
			wiphy_err(priv->hw->wiphy, "[WSM] TX Frames (%d) stuck in firmware, killing BH\n", priv->hw_bufs_used);
			wake_up(&priv->bh_wq);
			return false;
		}

		/* Ok, everything is flushed. */
		return true;
	}
}