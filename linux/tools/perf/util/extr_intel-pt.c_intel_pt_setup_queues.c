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
struct TYPE_2__ {unsigned int nr_queues; int /*<<< orphan*/ * queue_array; } ;
struct intel_pt {TYPE_1__ queues; } ;

/* Variables and functions */
 int intel_pt_setup_queue (struct intel_pt*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int intel_pt_setup_queues(struct intel_pt *pt)
{
	unsigned int i;
	int ret;

	for (i = 0; i < pt->queues.nr_queues; i++) {
		ret = intel_pt_setup_queue(pt, &pt->queues.queue_array[i], i);
		if (ret)
			return ret;
	}
	return 0;
}