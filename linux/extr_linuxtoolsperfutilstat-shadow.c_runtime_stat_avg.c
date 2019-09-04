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
struct saved_value {int /*<<< orphan*/  stats; } ;
struct runtime_stat {int dummy; } ;
typedef  enum stat_type { ____Placeholder_stat_type } stat_type ;

/* Variables and functions */
 double avg_stats (int /*<<< orphan*/ *) ; 
 struct saved_value* saved_value_lookup (int /*<<< orphan*/ *,int,int,int,int,struct runtime_stat*) ; 

__attribute__((used)) static double runtime_stat_avg(struct runtime_stat *st,
			       enum stat_type type, int ctx, int cpu)
{
	struct saved_value *v;

	v = saved_value_lookup(NULL, cpu, false, type, ctx, st);
	if (!v)
		return 0.0;

	return avg_stats(&v->stats);
}