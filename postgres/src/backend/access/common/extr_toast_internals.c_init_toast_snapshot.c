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
struct TYPE_5__ {int /*<<< orphan*/  whenTaken; int /*<<< orphan*/  lsn; } ;
typedef  TYPE_1__* Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GetOldestSnapshot () ; 
 int /*<<< orphan*/  InitToastSnapshot (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
init_toast_snapshot(Snapshot toast_snapshot)
{
	Snapshot	snapshot = GetOldestSnapshot();

	if (snapshot == NULL)
		elog(ERROR, "no known snapshots");

	InitToastSnapshot(*toast_snapshot, snapshot->lsn, snapshot->whenTaken);
}