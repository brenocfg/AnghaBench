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

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RecoveryInProgress () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
error_commit_ts_disabled(void)
{
	ereport(ERROR,
			(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
			 errmsg("could not get commit timestamp data"),
			 RecoveryInProgress() ?
			 errhint("Make sure the configuration parameter \"%s\" is set on the master server.",
					 "track_commit_timestamp") :
			 errhint("Make sure the configuration parameter \"%s\" is set.",
					 "track_commit_timestamp")));
}