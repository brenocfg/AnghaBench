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
typedef  int u32 ;
struct cw1200_queue_stats {scalar_t__ num_queued; int map_capacity; int /*<<< orphan*/  lock; scalar_t__* link_map_cache; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

bool cw1200_queue_stats_is_empty(struct cw1200_queue_stats *stats,
				 u32 link_id_map)
{
	bool empty = true;

	spin_lock_bh(&stats->lock);
	if (link_id_map == (u32)-1) {
		empty = stats->num_queued == 0;
	} else {
		int i;
		for (i = 0; i < stats->map_capacity; ++i) {
			if (link_id_map & BIT(i)) {
				if (stats->link_map_cache[i]) {
					empty = false;
					break;
				}
			}
		}
	}
	spin_unlock_bh(&stats->lock);

	return empty;
}