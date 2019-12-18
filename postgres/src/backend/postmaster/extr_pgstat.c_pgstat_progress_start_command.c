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
struct TYPE_5__ {int /*<<< orphan*/  st_progress_param; int /*<<< orphan*/  st_progress_command_target; int /*<<< orphan*/  st_progress_command; } ;
typedef  int /*<<< orphan*/  ProgressCommandType ;
typedef  TYPE_1__ PgBackendStatus ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* MyBEEntry ; 
 int /*<<< orphan*/  PGSTAT_BEGIN_WRITE_ACTIVITY (TYPE_1__ volatile*) ; 
 int /*<<< orphan*/  PGSTAT_END_WRITE_ACTIVITY (TYPE_1__ volatile*) ; 
 int /*<<< orphan*/  pgstat_track_activities ; 

void
pgstat_progress_start_command(ProgressCommandType cmdtype, Oid relid)
{
	volatile PgBackendStatus *beentry = MyBEEntry;

	if (!beentry || !pgstat_track_activities)
		return;

	PGSTAT_BEGIN_WRITE_ACTIVITY(beentry);
	beentry->st_progress_command = cmdtype;
	beentry->st_progress_command_target = relid;
	MemSet(&beentry->st_progress_param, 0, sizeof(beentry->st_progress_param));
	PGSTAT_END_WRITE_ACTIVITY(beentry);
}