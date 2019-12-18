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
struct auxtrace_queues {unsigned int nr_queues; struct auxtrace_queue* queue_array; } ;
struct auxtrace_queue {int /*<<< orphan*/  priv; int /*<<< orphan*/  set; int /*<<< orphan*/  cpu; int /*<<< orphan*/  tid; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 unsigned int AUXTRACE_INIT_NR_QUEUES ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct auxtrace_queue* auxtrace_alloc_queue_array (unsigned int) ; 
 int /*<<< orphan*/  list_splice_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int auxtrace_queues__grow(struct auxtrace_queues *queues,
				 unsigned int new_nr_queues)
{
	unsigned int nr_queues = queues->nr_queues;
	struct auxtrace_queue *queue_array;
	unsigned int i;

	if (!nr_queues)
		nr_queues = AUXTRACE_INIT_NR_QUEUES;

	while (nr_queues && nr_queues < new_nr_queues)
		nr_queues <<= 1;

	if (nr_queues < queues->nr_queues || nr_queues < new_nr_queues)
		return -EINVAL;

	queue_array = auxtrace_alloc_queue_array(nr_queues);
	if (!queue_array)
		return -ENOMEM;

	for (i = 0; i < queues->nr_queues; i++) {
		list_splice_tail(&queues->queue_array[i].head,
				 &queue_array[i].head);
		queue_array[i].tid = queues->queue_array[i].tid;
		queue_array[i].cpu = queues->queue_array[i].cpu;
		queue_array[i].set = queues->queue_array[i].set;
		queue_array[i].priv = queues->queue_array[i].priv;
	}

	queues->nr_queues = nr_queues;
	queues->queue_array = queue_array;

	return 0;
}