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
typedef  double u64 ;
struct TYPE_2__ {double period; } ;
struct hist_entry {TYPE_1__ stat; int /*<<< orphan*/  hists; } ;

/* Variables and functions */
 double hists__total_period (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double baseline_percent(struct hist_entry *he)
{
	u64 total = hists__total_period(he->hists);

	return 100.0 * he->stat.period / total;
}