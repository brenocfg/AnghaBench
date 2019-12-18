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
struct ff_circular_queue {void** slots; int /*<<< orphan*/  item_size; } ;

/* Variables and functions */
 void* av_mallocz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *queue_fetch_or_alloc(struct ff_circular_queue *cq, int index)
{
	if (cq->slots[index] == NULL)
		cq->slots[index] = av_mallocz(cq->item_size);

	return cq->slots[index];
}