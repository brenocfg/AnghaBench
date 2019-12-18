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
struct TYPE_3__ {scalar_t__ whenTaken; } ;
typedef  TYPE_1__* Snapshot ;
typedef  int /*<<< orphan*/  Relation ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SNAPSHOT_TOO_OLD ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetOldSnapshotThresholdTimestamp () ; 
 scalar_t__ RelationAllowsEarlyPruning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
TestForOldSnapshot_impl(Snapshot snapshot, Relation relation)
{
	if (RelationAllowsEarlyPruning(relation)
		&& (snapshot)->whenTaken < GetOldSnapshotThresholdTimestamp())
		ereport(ERROR,
				(errcode(ERRCODE_SNAPSHOT_TOO_OLD),
				 errmsg("snapshot too old")));
}