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
struct runtime_stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_TOPDOWN_FETCH_BUBBLES ; 
 double runtime_stat_avg (struct runtime_stat*,int /*<<< orphan*/ ,int,int) ; 
 double td_total_slots (int,int,struct runtime_stat*) ; 

__attribute__((used)) static double td_fe_bound(int ctx, int cpu, struct runtime_stat *st)
{
	double fe_bound = 0;
	double total_slots = td_total_slots(ctx, cpu, st);
	double fetch_bub = runtime_stat_avg(st, STAT_TOPDOWN_FETCH_BUBBLES,
					    ctx, cpu);

	if (total_slots)
		fe_bound = fetch_bub / total_slots;
	return fe_bound;
}