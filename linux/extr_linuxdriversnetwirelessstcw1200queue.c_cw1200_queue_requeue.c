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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct cw1200_queue_stats {int /*<<< orphan*/  lock; int /*<<< orphan*/ * link_map_cache; int /*<<< orphan*/  num_queued; } ;
struct TYPE_2__ {size_t link_id; } ;
struct cw1200_queue_item {size_t generation; int /*<<< orphan*/  head; int /*<<< orphan*/  packet_id; TYPE_1__ txpriv; } ;
struct cw1200_queue {size_t queue_id; size_t generation; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; int /*<<< orphan*/ * link_map_cache; int /*<<< orphan*/  num_pending; scalar_t__ capacity; struct cw1200_queue_item* pool; struct cw1200_queue_stats* stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cw1200_queue_mk_packet_id (size_t,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  cw1200_queue_parse_id (int /*<<< orphan*/ ,size_t*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int cw1200_queue_requeue(struct cw1200_queue *queue, u32 packet_id)
{
	int ret = 0;
	u8 queue_generation, queue_id, item_generation, item_id;
	struct cw1200_queue_item *item;
	struct cw1200_queue_stats *stats = queue->stats;

	cw1200_queue_parse_id(packet_id, &queue_generation, &queue_id,
			      &item_generation, &item_id);

	item = &queue->pool[item_id];

	spin_lock_bh(&queue->lock);
	BUG_ON(queue_id != queue->queue_id);
	if (queue_generation != queue->generation) {
		ret = -ENOENT;
	} else if (item_id >= (unsigned) queue->capacity) {
		WARN_ON(1);
		ret = -EINVAL;
	} else if (item->generation != item_generation) {
		WARN_ON(1);
		ret = -ENOENT;
	} else {
		--queue->num_pending;
		++queue->link_map_cache[item->txpriv.link_id];

		spin_lock_bh(&stats->lock);
		++stats->num_queued;
		++stats->link_map_cache[item->txpriv.link_id];
		spin_unlock_bh(&stats->lock);

		item->generation = ++item_generation;
		item->packet_id = cw1200_queue_mk_packet_id(queue_generation,
							    queue_id,
							    item_generation,
							    item_id);
		list_move(&item->head, &queue->queue);
	}
	spin_unlock_bh(&queue->lock);
	return ret;
}