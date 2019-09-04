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
struct sched_domain_topology_level {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct sched_domain_topology_level* sched_domain_topology ; 
 int /*<<< orphan*/  sched_smp_initialized ; 

void set_sched_topology(struct sched_domain_topology_level *tl)
{
	if (WARN_ON_ONCE(sched_smp_initialized))
		return;

	sched_domain_topology = tl;
}