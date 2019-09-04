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
struct sd_data {int /*<<< orphan*/  sgc; int /*<<< orphan*/  sg; int /*<<< orphan*/  sds; int /*<<< orphan*/  sd; } ;
struct sched_domain {int /*<<< orphan*/  ref; struct sd_data* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct sched_domain** per_cpu_ptr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void claim_allocations(int cpu, struct sched_domain *sd)
{
	struct sd_data *sdd = sd->private;

	WARN_ON_ONCE(*per_cpu_ptr(sdd->sd, cpu) != sd);
	*per_cpu_ptr(sdd->sd, cpu) = NULL;

	if (atomic_read(&(*per_cpu_ptr(sdd->sds, cpu))->ref))
		*per_cpu_ptr(sdd->sds, cpu) = NULL;

	if (atomic_read(&(*per_cpu_ptr(sdd->sg, cpu))->ref))
		*per_cpu_ptr(sdd->sg, cpu) = NULL;

	if (atomic_read(&(*per_cpu_ptr(sdd->sgc, cpu))->ref))
		*per_cpu_ptr(sdd->sgc, cpu) = NULL;
}