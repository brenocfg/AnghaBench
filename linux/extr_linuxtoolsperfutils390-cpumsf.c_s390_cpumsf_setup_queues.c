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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {unsigned int nr_queues; int /*<<< orphan*/ * queue_array; } ;
struct s390_cpumsf {TYPE_1__ queues; } ;

/* Variables and functions */
 int s390_cpumsf_setup_queue (struct s390_cpumsf*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s390_cpumsf_setup_queues(struct s390_cpumsf *sf, u64 ts)
{
	unsigned int i;
	int ret = 0;

	for (i = 0; i < sf->queues.nr_queues; i++) {
		ret = s390_cpumsf_setup_queue(sf, &sf->queues.queue_array[i],
					      i, ts);
		if (ret)
			break;
	}
	return ret;
}