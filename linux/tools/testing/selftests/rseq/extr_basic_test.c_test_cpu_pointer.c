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
typedef  int /*<<< orphan*/  test_affinity ;
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  int /*<<< orphan*/  affinity ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int CPU_SETSIZE ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int rseq_cpu_start () ; 
 int rseq_current_cpu () ; 
 int rseq_current_cpu_raw () ; 
 int /*<<< orphan*/  sched_getaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sched_getcpu () ; 
 int /*<<< orphan*/  sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void test_cpu_pointer(void)
{
	cpu_set_t affinity, test_affinity;
	int i;

	sched_getaffinity(0, sizeof(affinity), &affinity);
	CPU_ZERO(&test_affinity);
	for (i = 0; i < CPU_SETSIZE; i++) {
		if (CPU_ISSET(i, &affinity)) {
			CPU_SET(i, &test_affinity);
			sched_setaffinity(0, sizeof(test_affinity),
					&test_affinity);
			assert(sched_getcpu() == i);
			assert(rseq_current_cpu() == i);
			assert(rseq_current_cpu_raw() == i);
			assert(rseq_cpu_start() == i);
			CPU_CLR(i, &test_affinity);
		}
	}
	sched_setaffinity(0, sizeof(affinity), &affinity);
}