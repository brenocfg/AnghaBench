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
typedef  int /*<<< orphan*/  u8 ;
struct cw1200_queue_stats {size_t map_capacity; } ;
struct cw1200_queue_item {int dummy; } ;
struct cw1200_queue {size_t capacity; unsigned long ttl; int /*<<< orphan*/  free_pool; TYPE_1__* pool; void* link_map_cache; int /*<<< orphan*/  gc; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; int /*<<< orphan*/  queue; int /*<<< orphan*/  queue_id; struct cw1200_queue_stats* stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_queue_gc ; 
 void* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct cw1200_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cw1200_queue_init(struct cw1200_queue *queue,
		      struct cw1200_queue_stats *stats,
		      u8 queue_id,
		      size_t capacity,
		      unsigned long ttl)
{
	size_t i;

	memset(queue, 0, sizeof(*queue));
	queue->stats = stats;
	queue->capacity = capacity;
	queue->queue_id = queue_id;
	queue->ttl = ttl;
	INIT_LIST_HEAD(&queue->queue);
	INIT_LIST_HEAD(&queue->pending);
	INIT_LIST_HEAD(&queue->free_pool);
	spin_lock_init(&queue->lock);
	timer_setup(&queue->gc, cw1200_queue_gc, 0);

	queue->pool = kcalloc(capacity, sizeof(struct cw1200_queue_item),
			      GFP_KERNEL);
	if (!queue->pool)
		return -ENOMEM;

	queue->link_map_cache = kcalloc(stats->map_capacity, sizeof(int),
					GFP_KERNEL);
	if (!queue->link_map_cache) {
		kfree(queue->pool);
		queue->pool = NULL;
		return -ENOMEM;
	}

	for (i = 0; i < capacity; ++i)
		list_add_tail(&queue->pool[i].head, &queue->free_pool);

	return 0;
}