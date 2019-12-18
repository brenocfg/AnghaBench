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
struct data__file {int /*<<< orphan*/  session; } ;
struct TYPE_2__ {int /*<<< orphan*/  range_num; int /*<<< orphan*/  range_size; int /*<<< orphan*/  ptime_range; int /*<<< orphan*/  time_str; } ;

/* Variables and functions */
 TYPE_1__ pdiff ; 
 int perf_time__parse_for_ranges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_percent_time(struct data__file *d)
{
	int ret;

	ret = perf_time__parse_for_ranges(pdiff.time_str, d->session,
					  &pdiff.ptime_range,
					  &pdiff.range_size,
					  &pdiff.range_num);
	return ret;
}