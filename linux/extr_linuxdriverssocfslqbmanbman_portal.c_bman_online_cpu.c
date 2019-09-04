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
struct bman_portal {int dummy; } ;
struct bm_portal_config {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct bman_portal** affine_bportals ; 
 struct bm_portal_config* bman_get_bm_portal_config (struct bman_portal*) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  irq_set_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bman_online_cpu(unsigned int cpu)
{
	struct bman_portal *p = affine_bportals[cpu];
	const struct bm_portal_config *pcfg;

	if (!p)
		return 0;

	pcfg = bman_get_bm_portal_config(p);
	if (!pcfg)
		return 0;

	irq_set_affinity(pcfg->irq, cpumask_of(cpu));
	return 0;
}