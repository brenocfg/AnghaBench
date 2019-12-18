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
struct auxtrace_queues {int /*<<< orphan*/  queue_array; int /*<<< orphan*/  nr_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXTRACE_INIT_NR_QUEUES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  auxtrace_alloc_queue_array (int /*<<< orphan*/ ) ; 

int auxtrace_queues__init(struct auxtrace_queues *queues)
{
	queues->nr_queues = AUXTRACE_INIT_NR_QUEUES;
	queues->queue_array = auxtrace_alloc_queue_array(queues->nr_queues);
	if (!queues->queue_array)
		return -ENOMEM;
	return 0;
}