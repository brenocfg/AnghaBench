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
typedef  int u64 ;
struct em_perf_domain {unsigned long power; unsigned long frequency; int nr_cap_states; int /*<<< orphan*/  cpus; struct em_perf_domain* table; int /*<<< orphan*/  cost; } ;
struct em_data_callback {int (* active_power ) (unsigned long*,unsigned long*,int) ;} ;
struct em_cap_state {unsigned long power; unsigned long frequency; int nr_cap_states; int /*<<< orphan*/  cpus; struct em_cap_state* table; int /*<<< orphan*/  cost; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 unsigned long EM_CPU_MAX_POWER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cpumask_first (int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_size () ; 
 int /*<<< orphan*/  div64_u64 (int,unsigned long) ; 
 int /*<<< orphan*/  em_debug_create_pd (struct em_perf_domain*,int) ; 
 struct em_perf_domain* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct em_perf_domain*) ; 
 struct em_perf_domain* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,unsigned long) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int,int) ; 
 int stub1 (unsigned long*,unsigned long*,int) ; 
 int /*<<< orphan*/  to_cpumask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct em_perf_domain *em_create_pd(cpumask_t *span, int nr_states,
						struct em_data_callback *cb)
{
	unsigned long opp_eff, prev_opp_eff = ULONG_MAX;
	unsigned long power, freq, prev_freq = 0;
	int i, ret, cpu = cpumask_first(span);
	struct em_cap_state *table;
	struct em_perf_domain *pd;
	u64 fmax;

	if (!cb->active_power)
		return NULL;

	pd = kzalloc(sizeof(*pd) + cpumask_size(), GFP_KERNEL);
	if (!pd)
		return NULL;

	table = kcalloc(nr_states, sizeof(*table), GFP_KERNEL);
	if (!table)
		goto free_pd;

	/* Build the list of capacity states for this performance domain */
	for (i = 0, freq = 0; i < nr_states; i++, freq++) {
		/*
		 * active_power() is a driver callback which ceils 'freq' to
		 * lowest capacity state of 'cpu' above 'freq' and updates
		 * 'power' and 'freq' accordingly.
		 */
		ret = cb->active_power(&power, &freq, cpu);
		if (ret) {
			pr_err("pd%d: invalid cap. state: %d\n", cpu, ret);
			goto free_cs_table;
		}

		/*
		 * We expect the driver callback to increase the frequency for
		 * higher capacity states.
		 */
		if (freq <= prev_freq) {
			pr_err("pd%d: non-increasing freq: %lu\n", cpu, freq);
			goto free_cs_table;
		}

		/*
		 * The power returned by active_state() is expected to be
		 * positive, in milli-watts and to fit into 16 bits.
		 */
		if (!power || power > EM_CPU_MAX_POWER) {
			pr_err("pd%d: invalid power: %lu\n", cpu, power);
			goto free_cs_table;
		}

		table[i].power = power;
		table[i].frequency = prev_freq = freq;

		/*
		 * The hertz/watts efficiency ratio should decrease as the
		 * frequency grows on sane platforms. But this isn't always
		 * true in practice so warn the user if a higher OPP is more
		 * power efficient than a lower one.
		 */
		opp_eff = freq / power;
		if (opp_eff >= prev_opp_eff)
			pr_warn("pd%d: hertz/watts ratio non-monotonically decreasing: em_cap_state %d >= em_cap_state%d\n",
					cpu, i, i - 1);
		prev_opp_eff = opp_eff;
	}

	/* Compute the cost of each capacity_state. */
	fmax = (u64) table[nr_states - 1].frequency;
	for (i = 0; i < nr_states; i++) {
		table[i].cost = div64_u64(fmax * table[i].power,
					  table[i].frequency);
	}

	pd->table = table;
	pd->nr_cap_states = nr_states;
	cpumask_copy(to_cpumask(pd->cpus), span);

	em_debug_create_pd(pd, cpu);

	return pd;

free_cs_table:
	kfree(table);
free_pd:
	kfree(pd);

	return NULL;
}