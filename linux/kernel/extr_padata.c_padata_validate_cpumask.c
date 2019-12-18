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
struct padata_instance {int /*<<< orphan*/  flags; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PADATA_INVALID ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_intersects (struct cpumask const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool padata_validate_cpumask(struct padata_instance *pinst,
				    const struct cpumask *cpumask)
{
	if (!cpumask_intersects(cpumask, cpu_online_mask)) {
		pinst->flags |= PADATA_INVALID;
		return false;
	}

	pinst->flags &= ~PADATA_INVALID;
	return true;
}