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
typedef  int /*<<< orphan*/  TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 scalar_t__ IsAutoVacuumLauncherProcess () ; 
 int /*<<< orphan*/  STATS_READ_DELAY ; 
 int /*<<< orphan*/  TimestampDifferenceExceeds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_clear_snapshot () ; 

__attribute__((used)) static void
autovac_refresh_stats(void)
{
	if (IsAutoVacuumLauncherProcess())
	{
		static TimestampTz last_read = 0;
		TimestampTz current_time;

		current_time = GetCurrentTimestamp();

		if (!TimestampDifferenceExceeds(last_read, current_time,
										STATS_READ_DELAY))
			return;

		last_read = current_time;
	}

	pgstat_clear_snapshot();
}