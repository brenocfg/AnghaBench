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
struct thread_data {int tsc; int c1; scalar_t__ aperf; int mperf; int cpu_id; scalar_t__* counter; scalar_t__ smi_count; scalar_t__ irq_count; int /*<<< orphan*/  tv_end; int /*<<< orphan*/  tv_begin; int /*<<< orphan*/  tv_delta; int /*<<< orphan*/  x2apic_id; int /*<<< orphan*/  apic_id; } ;
struct msr_counter {scalar_t__ format; struct msr_counter* next; } ;
struct core_data {int c3; int c6; int c7; } ;
struct TYPE_2__ {struct msr_counter* tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIC_APIC ; 
 int /*<<< orphan*/  BIC_Avg_MHz ; 
 int /*<<< orphan*/  BIC_Busy ; 
 int /*<<< orphan*/  BIC_Bzy_MHz ; 
 int /*<<< orphan*/  BIC_IRQ ; 
 int /*<<< orphan*/  BIC_SMI ; 
 int /*<<< orphan*/  BIC_X2APIC ; 
 scalar_t__ DO_BIC (int /*<<< orphan*/ ) ; 
 scalar_t__ FORMAT_RAW ; 
 int debug ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  outf ; 
 scalar_t__ soft_c1_residency_display (int /*<<< orphan*/ ) ; 
 TYPE_1__ sys ; 
 int /*<<< orphan*/  timersub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tsc_tweak ; 
 scalar_t__ use_c1_residency_msr ; 

int
delta_thread(struct thread_data *new, struct thread_data *old,
	struct core_data *core_delta)
{
	int i;
	struct msr_counter *mp;

	/* we run cpuid just the 1st time, copy the results */
	if (DO_BIC(BIC_APIC))
		new->apic_id = old->apic_id;
	if (DO_BIC(BIC_X2APIC))
		new->x2apic_id = old->x2apic_id;

	/*
	 * the timestamps from start of measurement interval are in "old"
	 * the timestamp from end of measurement interval are in "new"
	 * over-write old w/ new so we can print end of interval values
	 */

	timersub(&new->tv_begin, &old->tv_begin, &old->tv_delta);
	old->tv_begin = new->tv_begin;
	old->tv_end = new->tv_end;

	old->tsc = new->tsc - old->tsc;

	/* check for TSC < 1 Mcycles over interval */
	if (old->tsc < (1000 * 1000))
		errx(-3, "Insanely slow TSC rate, TSC stops in idle?\n"
		     "You can disable all c-states by booting with \"idle=poll\"\n"
		     "or just the deep ones with \"processor.max_cstate=1\"");

	old->c1 = new->c1 - old->c1;

	if (DO_BIC(BIC_Avg_MHz) || DO_BIC(BIC_Busy) || DO_BIC(BIC_Bzy_MHz) ||
	    soft_c1_residency_display(BIC_Avg_MHz)) {
		if ((new->aperf > old->aperf) && (new->mperf > old->mperf)) {
			old->aperf = new->aperf - old->aperf;
			old->mperf = new->mperf - old->mperf;
		} else {
			return -1;
		}
	}


	if (use_c1_residency_msr) {
		/*
		 * Some models have a dedicated C1 residency MSR,
		 * which should be more accurate than the derivation below.
		 */
	} else {
		/*
		 * As counter collection is not atomic,
		 * it is possible for mperf's non-halted cycles + idle states
		 * to exceed TSC's all cycles: show c1 = 0% in that case.
		 */
		if ((old->mperf + core_delta->c3 + core_delta->c6 + core_delta->c7) > (old->tsc * tsc_tweak))
			old->c1 = 0;
		else {
			/* normal case, derive c1 */
			old->c1 = (old->tsc * tsc_tweak) - old->mperf - core_delta->c3
				- core_delta->c6 - core_delta->c7;
		}
	}

	if (old->mperf == 0) {
		if (debug > 1)
			fprintf(outf, "cpu%d MPERF 0!\n", old->cpu_id);
		old->mperf = 1;	/* divide by 0 protection */
	}

	if (DO_BIC(BIC_IRQ))
		old->irq_count = new->irq_count - old->irq_count;

	if (DO_BIC(BIC_SMI))
		old->smi_count = new->smi_count - old->smi_count;

	for (i = 0, mp = sys.tp; mp; i++, mp = mp->next) {
		if (mp->format == FORMAT_RAW)
			old->counter[i] = new->counter[i];
		else
			old->counter[i] = new->counter[i] - old->counter[i];
	}
	return 0;
}