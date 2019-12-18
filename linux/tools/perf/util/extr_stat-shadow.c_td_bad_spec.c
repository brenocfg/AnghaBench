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
 int /*<<< orphan*/  STAT_TOPDOWN_RECOVERY_BUBBLES ; 
 int /*<<< orphan*/  STAT_TOPDOWN_SLOTS_ISSUED ; 
 int /*<<< orphan*/  STAT_TOPDOWN_SLOTS_RETIRED ; 
 double runtime_stat_avg (struct runtime_stat*,int /*<<< orphan*/ ,int,int) ; 
 double sanitize_val (double) ; 
 double td_total_slots (int,int,struct runtime_stat*) ; 

__attribute__((used)) static double td_bad_spec(int ctx, int cpu, struct runtime_stat *st)
{
	double bad_spec = 0;
	double total_slots;
	double total;

	total = runtime_stat_avg(st, STAT_TOPDOWN_SLOTS_ISSUED, ctx, cpu) -
		runtime_stat_avg(st, STAT_TOPDOWN_SLOTS_RETIRED, ctx, cpu) +
		runtime_stat_avg(st, STAT_TOPDOWN_RECOVERY_BUBBLES, ctx, cpu);

	total_slots = td_total_slots(ctx, cpu, st);
	if (total_slots)
		bad_spec = total / total_slots;
	return sanitize_val(bad_spec);
}