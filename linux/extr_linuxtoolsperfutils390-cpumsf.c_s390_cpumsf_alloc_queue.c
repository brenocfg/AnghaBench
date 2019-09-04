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
struct s390_cpumsf_queue {unsigned int queue_nr; int cpu; struct s390_cpumsf* sf; } ;
struct s390_cpumsf {int dummy; } ;

/* Variables and functions */
 struct s390_cpumsf_queue* zalloc (int) ; 

__attribute__((used)) static struct s390_cpumsf_queue *
s390_cpumsf_alloc_queue(struct s390_cpumsf *sf, unsigned int queue_nr)
{
	struct s390_cpumsf_queue *sfq;

	sfq = zalloc(sizeof(struct s390_cpumsf_queue));
	if (sfq == NULL)
		return NULL;

	sfq->sf = sf;
	sfq->queue_nr = queue_nr;
	sfq->cpu = -1;
	return sfq;
}