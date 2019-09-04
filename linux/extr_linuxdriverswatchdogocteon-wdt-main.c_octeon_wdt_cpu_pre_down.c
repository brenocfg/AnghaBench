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
union cvmx_ciu_wdogx {int u64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_PP_POKEX (unsigned int) ; 
 int /*<<< orphan*/  CVMX_CIU_WDOGX (unsigned int) ; 
 unsigned int cpu2core (unsigned int) ; 
 int cpu_to_node (unsigned int) ; 
 int /*<<< orphan*/  cvmx_write_csr_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_wdt_cpu_to_irq (unsigned int) ; 
 int /*<<< orphan*/  octeon_wdt_poke_irq ; 

__attribute__((used)) static int octeon_wdt_cpu_pre_down(unsigned int cpu)
{
	unsigned int core;
	int node;
	union cvmx_ciu_wdogx ciu_wdog;

	core = cpu2core(cpu);

	node = cpu_to_node(cpu);

	/* Poke the watchdog to clear out its state */
	cvmx_write_csr_node(node, CVMX_CIU_PP_POKEX(core), 1);

	/* Disable the hardware. */
	ciu_wdog.u64 = 0;
	cvmx_write_csr_node(node, CVMX_CIU_WDOGX(core), ciu_wdog.u64);

	free_irq(octeon_wdt_cpu_to_irq(cpu), octeon_wdt_poke_irq);
	return 0;
}