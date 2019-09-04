#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  double u64 ;
struct TYPE_4__ {double period; } ;
struct hist_entry {TYPE_2__* stat_acc; int /*<<< orphan*/  hists; TYPE_1__ stat; } ;
struct TYPE_6__ {scalar_t__ cumulate_callchain; } ;
struct TYPE_5__ {double period; } ;

/* Variables and functions */
 double hists__total_period (int /*<<< orphan*/ ) ; 
 TYPE_3__ symbol_conf ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline float hist_entry__get_percent_limit(struct hist_entry *he)
{
	u64 period = he->stat.period;
	u64 total_period = hists__total_period(he->hists);

	if (unlikely(total_period == 0))
		return 0;

	if (symbol_conf.cumulate_callchain)
		period = he->stat_acc->period;

	return period * 100.0 / total_period;
}