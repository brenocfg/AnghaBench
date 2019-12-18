#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thread_data {int dummy; } ;
struct pkg_data {int dummy; } ;
struct msr_counter {scalar_t__ format; scalar_t__ type; struct msr_counter* next; } ;
struct core_data {int dummy; } ;
struct TYPE_11__ {int pkg_wtd_core_c0; int pkg_any_core_c0; int pkg_any_gfxe_c0; int pkg_both_core_gfxe_c0; int pc2; int pc3; int pc6; int pc7; int pc8; int pc9; int pc10; int* counter; } ;
struct TYPE_10__ {int c3; int c6; int c7; int mc6_us; int* counter; } ;
struct TYPE_9__ {int tsc; int aperf; int mperf; int c1; int irq_count; int* counter; int /*<<< orphan*/  tv_delta; } ;
struct TYPE_12__ {TYPE_5__ packages; TYPE_4__ cores; TYPE_3__ threads; } ;
struct TYPE_8__ {struct msr_counter* pp; struct msr_counter* cp; struct msr_counter* tp; } ;
struct TYPE_7__ {int num_cpus; int num_cores; int num_packages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIC_Any_c0 ; 
 int /*<<< orphan*/  BIC_CPUGFX ; 
 int /*<<< orphan*/  BIC_GFX_c0 ; 
 int /*<<< orphan*/  BIC_Pkgpc3 ; 
 int /*<<< orphan*/  BIC_Pkgpc6 ; 
 int /*<<< orphan*/  BIC_Pkgpc7 ; 
 int /*<<< orphan*/  BIC_Totl_c0 ; 
 scalar_t__ COUNTER_ITEMS ; 
 scalar_t__ DO_BIC (int /*<<< orphan*/ ) ; 
 scalar_t__ FORMAT_RAW ; 
 TYPE_6__ average ; 
 int /*<<< orphan*/  clear_counters (TYPE_3__*,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  for_all_cpus (int /*<<< orphan*/ ,struct thread_data*,struct core_data*,struct pkg_data*) ; 
 int /*<<< orphan*/  sum_counters ; 
 int sums_need_wide_columns ; 
 TYPE_2__ sys ; 
 TYPE_1__ topo ; 
 int /*<<< orphan*/  tv_delta ; 

void compute_average(struct thread_data *t, struct core_data *c,
	struct pkg_data *p)
{
	int i;
	struct msr_counter *mp;

	clear_counters(&average.threads, &average.cores, &average.packages);

	for_all_cpus(sum_counters, t, c, p);

	/* Use the global time delta for the average. */
	average.threads.tv_delta = tv_delta;

	average.threads.tsc /= topo.num_cpus;
	average.threads.aperf /= topo.num_cpus;
	average.threads.mperf /= topo.num_cpus;
	average.threads.c1 /= topo.num_cpus;

	if (average.threads.irq_count > 9999999)
		sums_need_wide_columns = 1;

	average.cores.c3 /= topo.num_cores;
	average.cores.c6 /= topo.num_cores;
	average.cores.c7 /= topo.num_cores;
	average.cores.mc6_us /= topo.num_cores;

	if (DO_BIC(BIC_Totl_c0))
		average.packages.pkg_wtd_core_c0 /= topo.num_packages;
	if (DO_BIC(BIC_Any_c0))
		average.packages.pkg_any_core_c0 /= topo.num_packages;
	if (DO_BIC(BIC_GFX_c0))
		average.packages.pkg_any_gfxe_c0 /= topo.num_packages;
	if (DO_BIC(BIC_CPUGFX))
		average.packages.pkg_both_core_gfxe_c0 /= topo.num_packages;

	average.packages.pc2 /= topo.num_packages;
	if (DO_BIC(BIC_Pkgpc3))
		average.packages.pc3 /= topo.num_packages;
	if (DO_BIC(BIC_Pkgpc6))
		average.packages.pc6 /= topo.num_packages;
	if (DO_BIC(BIC_Pkgpc7))
		average.packages.pc7 /= topo.num_packages;

	average.packages.pc8 /= topo.num_packages;
	average.packages.pc9 /= topo.num_packages;
	average.packages.pc10 /= topo.num_packages;

	for (i = 0, mp = sys.tp; mp; i++, mp = mp->next) {
		if (mp->format == FORMAT_RAW)
			continue;
		if (mp->type == COUNTER_ITEMS) {
			if (average.threads.counter[i] > 9999999)
				sums_need_wide_columns = 1;
			continue;
		}
		average.threads.counter[i] /= topo.num_cpus;
	}
	for (i = 0, mp = sys.cp; mp; i++, mp = mp->next) {
		if (mp->format == FORMAT_RAW)
			continue;
		if (mp->type == COUNTER_ITEMS) {
			if (average.cores.counter[i] > 9999999)
				sums_need_wide_columns = 1;
		}
		average.cores.counter[i] /= topo.num_cores;
	}
	for (i = 0, mp = sys.pp; mp; i++, mp = mp->next) {
		if (mp->format == FORMAT_RAW)
			continue;
		if (mp->type == COUNTER_ITEMS) {
			if (average.packages.counter[i] > 9999999)
				sums_need_wide_columns = 1;
		}
		average.packages.counter[i] /= topo.num_packages;
	}
}