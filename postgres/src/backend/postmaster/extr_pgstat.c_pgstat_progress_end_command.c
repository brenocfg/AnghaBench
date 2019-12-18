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
struct TYPE_5__ {scalar_t__ st_progress_command; int /*<<< orphan*/  st_progress_command_target; } ;
typedef  TYPE_1__ PgBackendStatus ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 TYPE_1__* MyBEEntry ; 
 int /*<<< orphan*/  PGSTAT_BEGIN_WRITE_ACTIVITY (TYPE_1__ volatile*) ; 
 int /*<<< orphan*/  PGSTAT_END_WRITE_ACTIVITY (TYPE_1__ volatile*) ; 
 scalar_t__ PROGRESS_COMMAND_INVALID ; 
 int /*<<< orphan*/  pgstat_track_activities ; 

void
pgstat_progress_end_command(void)
{
	volatile PgBackendStatus *beentry = MyBEEntry;

	if (!beentry || !pgstat_track_activities)
		return;

	if (beentry->st_progress_command == PROGRESS_COMMAND_INVALID)
		return;

	PGSTAT_BEGIN_WRITE_ACTIVITY(beentry);
	beentry->st_progress_command = PROGRESS_COMMAND_INVALID;
	beentry->st_progress_command_target = InvalidOid;
	PGSTAT_END_WRITE_ACTIVITY(beentry);
}