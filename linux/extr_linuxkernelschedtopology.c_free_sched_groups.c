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
struct sched_group {int /*<<< orphan*/  ref; struct sched_group* sgc; struct sched_group* next; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sched_group*) ; 

__attribute__((used)) static void free_sched_groups(struct sched_group *sg, int free_sgc)
{
	struct sched_group *tmp, *first;

	if (!sg)
		return;

	first = sg;
	do {
		tmp = sg->next;

		if (free_sgc && atomic_dec_and_test(&sg->sgc->ref))
			kfree(sg->sgc);

		if (atomic_dec_and_test(&sg->ref))
			kfree(sg);
		sg = tmp;
	} while (sg != first);
}