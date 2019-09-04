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
struct cs_etm_auxtrace {TYPE_1__ queues; } ;

/* Variables and functions */
 int cs_etm__setup_queue (struct cs_etm_auxtrace*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int cs_etm__setup_queues(struct cs_etm_auxtrace *etm)
{
	unsigned int i;
	int ret;

	for (i = 0; i < etm->queues.nr_queues; i++) {
		ret = cs_etm__setup_queue(etm, &etm->queues.queue_array[i], i);
		if (ret)
			return ret;
	}

	return 0;
}