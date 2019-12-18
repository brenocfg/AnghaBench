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
struct TYPE_2__ {double period_ratio_delta; double period_ratio; scalar_t__ wdiff; } ;
struct hist_entry {TYPE_1__ diff; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  COMPUTE_DELTA 131 
#define  COMPUTE_DELTA_ABS 130 
#define  COMPUTE_RATIO 129 
#define  COMPUTE_WEIGHTED_DIFF 128 
 scalar_t__ cmp_doubles (double,double) ; 
 double fabs (double) ; 

__attribute__((used)) static int64_t
__hist_entry__cmp_compute(struct hist_entry *left, struct hist_entry *right,
			int c)
{
	switch (c) {
	case COMPUTE_DELTA:
	{
		double l = left->diff.period_ratio_delta;
		double r = right->diff.period_ratio_delta;

		return cmp_doubles(l, r);
	}
	case COMPUTE_DELTA_ABS:
	{
		double l = fabs(left->diff.period_ratio_delta);
		double r = fabs(right->diff.period_ratio_delta);

		return cmp_doubles(l, r);
	}
	case COMPUTE_RATIO:
	{
		double l = left->diff.period_ratio;
		double r = right->diff.period_ratio;

		return cmp_doubles(l, r);
	}
	case COMPUTE_WEIGHTED_DIFF:
	{
		s64 l = left->diff.wdiff;
		s64 r = right->diff.wdiff;

		return r - l;
	}
	default:
		BUG_ON(1);
	}

	return 0;
}