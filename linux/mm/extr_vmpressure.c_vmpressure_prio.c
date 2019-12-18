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
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  vmpressure (int /*<<< orphan*/ ,struct mem_cgroup*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmpressure_level_critical_prio ; 
 int /*<<< orphan*/  vmpressure_win ; 

void vmpressure_prio(gfp_t gfp, struct mem_cgroup *memcg, int prio)
{
	/*
	 * We only use prio for accounting critical level. For more info
	 * see comment for vmpressure_level_critical_prio variable above.
	 */
	if (prio > vmpressure_level_critical_prio)
		return;

	/*
	 * OK, the prio is below the threshold, updating vmpressure
	 * information before shrinker dives into long shrinking of long
	 * range vmscan. Passing scanned = vmpressure_win, reclaimed = 0
	 * to the vmpressure() basically means that we signal 'critical'
	 * level.
	 */
	vmpressure(gfp, memcg, true, vmpressure_win, 0);
}