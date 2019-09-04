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
struct ff_circular_queue {int /*<<< orphan*/  write_index; } ;

/* Variables and functions */
 void* queue_fetch_or_alloc (struct ff_circular_queue*,int /*<<< orphan*/ ) ; 

void *ff_circular_queue_peek_write(struct ff_circular_queue *cq)
{
	return queue_fetch_or_alloc(cq, cq->write_index);
}