#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct data_queue {int /*<<< orphan*/  status_lock; TYPE_3__* rt2x00dev; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {TYPE_1__* lib; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop_queue ) (struct data_queue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_STARTED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00queue_pause_queue_nocheck (struct data_queue*) ; 
 int /*<<< orphan*/  stub1 (struct data_queue*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00queue_stop_queue(struct data_queue *queue)
{
	mutex_lock(&queue->status_lock);

	if (!test_and_clear_bit(QUEUE_STARTED, &queue->flags)) {
		mutex_unlock(&queue->status_lock);
		return;
	}

	rt2x00queue_pause_queue_nocheck(queue);

	queue->rt2x00dev->ops->lib->stop_queue(queue);

	mutex_unlock(&queue->status_lock);
}