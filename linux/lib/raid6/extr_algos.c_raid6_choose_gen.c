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
struct raid6_calls {scalar_t__ prefer; int /*<<< orphan*/  (* xor_syndrome ) (int const,int,int,int /*<<< orphan*/ ,void**) ;int /*<<< orphan*/  name; int /*<<< orphan*/  (* gen_syndrome ) (int const,int /*<<< orphan*/ ,void**) ;int /*<<< orphan*/  (* valid ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RAID6_PQ_BENCHMARK ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int RAID6_TIME_JIFFIES_LG2 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,...) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct raid6_calls** raid6_algos ; 
 struct raid6_calls raid6_call ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (int const,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub3 (int const,int,int,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static inline const struct raid6_calls *raid6_choose_gen(
	void *(*const dptrs)[(65536/PAGE_SIZE)+2], const int disks)
{
	unsigned long perf, bestgenperf, bestxorperf, j0, j1;
	int start = (disks>>1)-1, stop = disks-3;	/* work on the second half of the disks */
	const struct raid6_calls *const *algo;
	const struct raid6_calls *best;

	for (bestgenperf = 0, bestxorperf = 0, best = NULL, algo = raid6_algos; *algo; algo++) {
		if (!best || (*algo)->prefer >= best->prefer) {
			if ((*algo)->valid && !(*algo)->valid())
				continue;

			if (!IS_ENABLED(CONFIG_RAID6_PQ_BENCHMARK)) {
				best = *algo;
				break;
			}

			perf = 0;

			preempt_disable();
			j0 = jiffies;
			while ((j1 = jiffies) == j0)
				cpu_relax();
			while (time_before(jiffies,
					    j1 + (1<<RAID6_TIME_JIFFIES_LG2))) {
				(*algo)->gen_syndrome(disks, PAGE_SIZE, *dptrs);
				perf++;
			}
			preempt_enable();

			if (perf > bestgenperf) {
				bestgenperf = perf;
				best = *algo;
			}
			pr_info("raid6: %-8s gen() %5ld MB/s\n", (*algo)->name,
			       (perf*HZ) >> (20-16+RAID6_TIME_JIFFIES_LG2));

			if (!(*algo)->xor_syndrome)
				continue;

			perf = 0;

			preempt_disable();
			j0 = jiffies;
			while ((j1 = jiffies) == j0)
				cpu_relax();
			while (time_before(jiffies,
					    j1 + (1<<RAID6_TIME_JIFFIES_LG2))) {
				(*algo)->xor_syndrome(disks, start, stop,
						      PAGE_SIZE, *dptrs);
				perf++;
			}
			preempt_enable();

			if (best == *algo)
				bestxorperf = perf;

			pr_info("raid6: %-8s xor() %5ld MB/s\n", (*algo)->name,
				(perf*HZ) >> (20-16+RAID6_TIME_JIFFIES_LG2+1));
		}
	}

	if (best) {
		pr_info("raid6: using algorithm %s gen() %ld MB/s\n",
		       best->name,
		       (bestgenperf*HZ) >> (20-16+RAID6_TIME_JIFFIES_LG2));
		if (best->xor_syndrome)
			pr_info("raid6: .... xor() %ld MB/s, rmw enabled\n",
			       (bestxorperf*HZ) >> (20-16+RAID6_TIME_JIFFIES_LG2+1));
		raid6_call = *best;
	} else
		pr_err("raid6: Yikes!  No algorithm found!\n");

	return best;
}