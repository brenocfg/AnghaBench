#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct thread_data {int flags; scalar_t__* counter; scalar_t__ smi_count; scalar_t__ irq_count; scalar_t__ c1; scalar_t__ mperf; scalar_t__ aperf; scalar_t__ tsc; TYPE_3__ tv_delta; TYPE_2__ tv_end; TYPE_1__ tv_begin; } ;
struct pkg_data {scalar_t__* counter; scalar_t__ gfx_mhz; scalar_t__ gfx_rc6_ms; scalar_t__ pkg_temp_c; scalar_t__ rapl_dram_perf_status; scalar_t__ rapl_pkg_perf_status; scalar_t__ energy_gfx; scalar_t__ energy_cores; scalar_t__ energy_dram; scalar_t__ energy_pkg; scalar_t__ sys_lpi; scalar_t__ cpu_lpi; scalar_t__ pc10; scalar_t__ pc9; scalar_t__ pc8; scalar_t__ pc7; scalar_t__ pc6; scalar_t__ pc3; scalar_t__ pc2; scalar_t__ pkg_both_core_gfxe_c0; scalar_t__ pkg_any_gfxe_c0; scalar_t__ pkg_any_core_c0; scalar_t__ pkg_wtd_core_c0; } ;
struct msr_counter {struct msr_counter* next; } ;
struct core_data {scalar_t__* counter; scalar_t__ core_energy; scalar_t__ core_temp_c; scalar_t__ mc6_us; scalar_t__ c7; scalar_t__ c6; scalar_t__ c3; } ;
struct TYPE_8__ {struct msr_counter* pp; struct msr_counter* cp; struct msr_counter* tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIC_Pkgpc3 ; 
 int /*<<< orphan*/  BIC_Pkgpc6 ; 
 int /*<<< orphan*/  BIC_Pkgpc7 ; 
 int CPU_IS_FIRST_CORE_IN_PACKAGE ; 
 int CPU_IS_FIRST_THREAD_IN_CORE ; 
 scalar_t__ DO_BIC (int /*<<< orphan*/ ) ; 
 TYPE_4__ sys ; 

void clear_counters(struct thread_data *t, struct core_data *c, struct pkg_data *p)
{
	int i;
	struct msr_counter  *mp;

	t->tv_begin.tv_sec = 0;
	t->tv_begin.tv_usec = 0;
	t->tv_end.tv_sec = 0;
	t->tv_end.tv_usec = 0;
	t->tv_delta.tv_sec = 0;
	t->tv_delta.tv_usec = 0;

	t->tsc = 0;
	t->aperf = 0;
	t->mperf = 0;
	t->c1 = 0;

	t->irq_count = 0;
	t->smi_count = 0;

	/* tells format_counters to dump all fields from this set */
	t->flags = CPU_IS_FIRST_THREAD_IN_CORE | CPU_IS_FIRST_CORE_IN_PACKAGE;

	c->c3 = 0;
	c->c6 = 0;
	c->c7 = 0;
	c->mc6_us = 0;
	c->core_temp_c = 0;
	c->core_energy = 0;

	p->pkg_wtd_core_c0 = 0;
	p->pkg_any_core_c0 = 0;
	p->pkg_any_gfxe_c0 = 0;
	p->pkg_both_core_gfxe_c0 = 0;

	p->pc2 = 0;
	if (DO_BIC(BIC_Pkgpc3))
		p->pc3 = 0;
	if (DO_BIC(BIC_Pkgpc6))
		p->pc6 = 0;
	if (DO_BIC(BIC_Pkgpc7))
		p->pc7 = 0;
	p->pc8 = 0;
	p->pc9 = 0;
	p->pc10 = 0;
	p->cpu_lpi = 0;
	p->sys_lpi = 0;

	p->energy_pkg = 0;
	p->energy_dram = 0;
	p->energy_cores = 0;
	p->energy_gfx = 0;
	p->rapl_pkg_perf_status = 0;
	p->rapl_dram_perf_status = 0;
	p->pkg_temp_c = 0;

	p->gfx_rc6_ms = 0;
	p->gfx_mhz = 0;
	for (i = 0, mp = sys.tp; mp; i++, mp = mp->next)
		t->counter[i] = 0;

	for (i = 0, mp = sys.cp; mp; i++, mp = mp->next)
		c->counter[i] = 0;

	for (i = 0, mp = sys.pp; mp; i++, mp = mp->next)
		p->counter[i] = 0;
}