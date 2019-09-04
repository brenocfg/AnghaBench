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
struct sched_domain {unsigned long flags; TYPE_1__* groups; } ;
struct TYPE_2__ {struct TYPE_2__* next; } ;

/* Variables and functions */
 unsigned long SD_ASYM_CPUCAPACITY ; 
 unsigned long SD_BALANCE_EXEC ; 
 unsigned long SD_BALANCE_FORK ; 
 unsigned long SD_BALANCE_NEWIDLE ; 
 unsigned long SD_LOAD_BALANCE ; 
 unsigned long SD_PREFER_SIBLING ; 
 unsigned long SD_SERIALIZE ; 
 unsigned long SD_SHARE_CPUCAPACITY ; 
 unsigned long SD_SHARE_PKG_RESOURCES ; 
 unsigned long SD_SHARE_POWERDOMAIN ; 
 int /*<<< orphan*/  cpumask_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nr_node_ids ; 
 int /*<<< orphan*/  sched_domain_span (struct sched_domain*) ; 
 scalar_t__ sd_degenerate (struct sched_domain*) ; 

__attribute__((used)) static int
sd_parent_degenerate(struct sched_domain *sd, struct sched_domain *parent)
{
	unsigned long cflags = sd->flags, pflags = parent->flags;

	if (sd_degenerate(parent))
		return 1;

	if (!cpumask_equal(sched_domain_span(sd), sched_domain_span(parent)))
		return 0;

	/* Flags needing groups don't count if only 1 group in parent */
	if (parent->groups == parent->groups->next) {
		pflags &= ~(SD_LOAD_BALANCE |
				SD_BALANCE_NEWIDLE |
				SD_BALANCE_FORK |
				SD_BALANCE_EXEC |
				SD_ASYM_CPUCAPACITY |
				SD_SHARE_CPUCAPACITY |
				SD_SHARE_PKG_RESOURCES |
				SD_PREFER_SIBLING |
				SD_SHARE_POWERDOMAIN);
		if (nr_node_ids == 1)
			pflags &= ~SD_SERIALIZE;
	}
	if (~cflags & pflags)
		return 0;

	return 1;
}