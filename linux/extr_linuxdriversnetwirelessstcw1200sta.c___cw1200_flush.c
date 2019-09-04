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
struct TYPE_2__ {int /*<<< orphan*/  wait_link_id_empty; } ;
struct cw1200_common {TYPE_1__ tx_queue_stats; int /*<<< orphan*/ * tx_queue; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  cw1200_queue_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_queue_stats_is_empty (TYPE_1__*,int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wsm_lock_tx (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

__attribute__((used)) static int __cw1200_flush(struct cw1200_common *priv, bool drop)
{
	int i, ret;

	for (;;) {
		/* TODO: correct flush handling is required when dev_stop.
		 * Temporary workaround: 2s
		 */
		if (drop) {
			for (i = 0; i < 4; ++i)
				cw1200_queue_clear(&priv->tx_queue[i]);
		} else {
			ret = wait_event_timeout(
				priv->tx_queue_stats.wait_link_id_empty,
				cw1200_queue_stats_is_empty(
					&priv->tx_queue_stats, -1),
				2 * HZ);
		}

		if (!drop && ret <= 0) {
			ret = -ETIMEDOUT;
			break;
		} else {
			ret = 0;
		}

		wsm_lock_tx(priv);
		if (!cw1200_queue_stats_is_empty(&priv->tx_queue_stats, -1)) {
			/* Highly unlikely: WSM requeued frames. */
			wsm_unlock_tx(priv);
			continue;
		}
		break;
	}
	return ret;
}