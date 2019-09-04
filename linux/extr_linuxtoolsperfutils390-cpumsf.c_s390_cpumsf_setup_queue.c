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
typedef  int /*<<< orphan*/  u64 ;
struct s390_cpumsf_queue {int cpu; } ;
struct s390_cpumsf {int /*<<< orphan*/  heap; } ;
struct auxtrace_queue {int cpu; struct s390_cpumsf_queue* priv; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int ENOMEM ; 
 int auxtrace_heap__add (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct s390_cpumsf_queue* s390_cpumsf_alloc_queue (struct s390_cpumsf*,unsigned int) ; 

__attribute__((used)) static int s390_cpumsf_setup_queue(struct s390_cpumsf *sf,
				   struct auxtrace_queue *queue,
				   unsigned int queue_nr, u64 ts)
{
	struct s390_cpumsf_queue *sfq = queue->priv;

	if (list_empty(&queue->head))
		return 0;

	if (sfq == NULL) {
		sfq = s390_cpumsf_alloc_queue(sf, queue_nr);
		if (!sfq)
			return -ENOMEM;
		queue->priv = sfq;

		if (queue->cpu != -1)
			sfq->cpu = queue->cpu;
	}
	return auxtrace_heap__add(&sf->heap, queue_nr, ts);
}