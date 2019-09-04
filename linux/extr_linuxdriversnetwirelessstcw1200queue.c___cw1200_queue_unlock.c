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
struct cw1200_queue_stats {TYPE_1__* priv; } ;
struct cw1200_queue {scalar_t__ tx_locked_cnt; int /*<<< orphan*/  queue_id; struct cw1200_queue_stats* stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __cw1200_queue_unlock(struct cw1200_queue *queue)
{
	struct cw1200_queue_stats *stats = queue->stats;
	BUG_ON(!queue->tx_locked_cnt);
	if (--queue->tx_locked_cnt == 0) {
		pr_debug("[TX] Queue %d is unlocked.\n",
			 queue->queue_id);
		ieee80211_wake_queue(stats->priv->hw, queue->queue_id);
	}
}