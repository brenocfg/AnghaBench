#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_5__ {int /*<<< orphan*/  st_xact_start_timestamp; } ;
typedef  TYPE_1__ PgBackendStatus ;

/* Variables and functions */
 TYPE_1__* MyBEEntry ; 
 int /*<<< orphan*/  PGSTAT_BEGIN_WRITE_ACTIVITY (TYPE_1__ volatile*) ; 
 int /*<<< orphan*/  PGSTAT_END_WRITE_ACTIVITY (TYPE_1__ volatile*) ; 
 int /*<<< orphan*/  pgstat_track_activities ; 

void
pgstat_report_xact_timestamp(TimestampTz tstamp)
{
	volatile PgBackendStatus *beentry = MyBEEntry;

	if (!pgstat_track_activities || !beentry)
		return;

	/*
	 * Update my status entry, following the protocol of bumping
	 * st_changecount before and after.  We use a volatile pointer here to
	 * ensure the compiler doesn't try to get cute.
	 */
	PGSTAT_BEGIN_WRITE_ACTIVITY(beentry);

	beentry->st_xact_start_timestamp = tstamp;

	PGSTAT_END_WRITE_ACTIVITY(beentry);
}