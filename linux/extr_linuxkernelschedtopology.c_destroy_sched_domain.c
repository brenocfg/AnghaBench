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
struct sched_domain {struct sched_domain* shared; int /*<<< orphan*/  ref; int /*<<< orphan*/  groups; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_sched_groups (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct sched_domain*) ; 

__attribute__((used)) static void destroy_sched_domain(struct sched_domain *sd)
{
	/*
	 * A normal sched domain may have multiple group references, an
	 * overlapping domain, having private groups, only one.  Iterate,
	 * dropping group/capacity references, freeing where none remain.
	 */
	free_sched_groups(sd->groups, 1);

	if (sd->shared && atomic_dec_and_test(&sd->shared->ref))
		kfree(sd->shared);
	kfree(sd);
}