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
typedef  int /*<<< orphan*/  u16 ;
struct qman_portal {TYPE_1__* config; } ;
struct TYPE_2__ {int cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * affine_channels ; 
 int /*<<< orphan*/  affine_mask ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 struct qman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  put_affine_portal () ; 

u16 qman_affine_channel(int cpu)
{
	if (cpu < 0) {
		struct qman_portal *portal = get_affine_portal();

		cpu = portal->config->cpu;
		put_affine_portal();
	}
	WARN_ON(!cpumask_test_cpu(cpu, &affine_mask));
	return affine_channels[cpu];
}