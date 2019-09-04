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
struct rt2x00_dev {TYPE_1__* ops; } ;
struct data_queue {int qid; int aifs; int cw_min; int cw_max; int /*<<< orphan*/  limit; int /*<<< orphan*/  threshold; scalar_t__ txop; struct rt2x00_dev* rt2x00dev; int /*<<< orphan*/  index_lock; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  status_lock; } ;
typedef  enum data_queue_qid { ____Placeholder_data_queue_qid } data_queue_qid ;
struct TYPE_2__ {int /*<<< orphan*/  (* queue_init ) (struct data_queue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct data_queue*) ; 

__attribute__((used)) static void rt2x00queue_init(struct rt2x00_dev *rt2x00dev,
			     struct data_queue *queue, enum data_queue_qid qid)
{
	mutex_init(&queue->status_lock);
	spin_lock_init(&queue->tx_lock);
	spin_lock_init(&queue->index_lock);

	queue->rt2x00dev = rt2x00dev;
	queue->qid = qid;
	queue->txop = 0;
	queue->aifs = 2;
	queue->cw_min = 5;
	queue->cw_max = 10;

	rt2x00dev->ops->queue_init(queue);

	queue->threshold = DIV_ROUND_UP(queue->limit, 10);
}