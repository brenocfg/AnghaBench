#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  list; int /*<<< orphan*/ * SCpnt; } ;
struct TYPE_6__ {TYPE_2__* alloc; int /*<<< orphan*/  free; int /*<<< orphan*/  head; int /*<<< orphan*/  queue_lock; } ;
typedef  TYPE_1__ Queue_t ;
typedef  TYPE_2__ QE_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int NR_QE ; 
 int /*<<< orphan*/  QUEUE_MAGIC_FREE ; 
 int /*<<< orphan*/  SET_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int queue_initialise (Queue_t *queue)
{
	unsigned int nqueues = NR_QE;
	QE_t *q;

	spin_lock_init(&queue->queue_lock);
	INIT_LIST_HEAD(&queue->head);
	INIT_LIST_HEAD(&queue->free);

	/*
	 * If life was easier, then SCpnt would have a
	 * host-available list head, and we wouldn't
	 * need to keep free lists or allocate this
	 * memory.
	 */
	queue->alloc = q = kmalloc_array(nqueues, sizeof(QE_t), GFP_KERNEL);
	if (q) {
		for (; nqueues; q++, nqueues--) {
			SET_MAGIC(q, QUEUE_MAGIC_FREE);
			q->SCpnt = NULL;
			list_add(&q->list, &queue->free);
		}
	}

	return queue->alloc != NULL;
}