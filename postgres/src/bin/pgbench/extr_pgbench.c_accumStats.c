#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lag; int /*<<< orphan*/  latency; int /*<<< orphan*/  skipped; int /*<<< orphan*/  cnt; } ;
typedef  TYPE_1__ StatsData ;

/* Variables and functions */
 int /*<<< orphan*/  addToSimpleStats (int /*<<< orphan*/ *,double) ; 
 scalar_t__ throttle_delay ; 

__attribute__((used)) static void
accumStats(StatsData *stats, bool skipped, double lat, double lag)
{
	stats->cnt++;

	if (skipped)
	{
		/* no latency to record on skipped transactions */
		stats->skipped++;
	}
	else
	{
		addToSimpleStats(&stats->latency, lat);

		/* and possibly the same for schedule lag */
		if (throttle_delay)
			addToSimpleStats(&stats->lag, lag);
	}
}