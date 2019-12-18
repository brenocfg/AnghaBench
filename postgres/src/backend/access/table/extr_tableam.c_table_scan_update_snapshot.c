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
typedef  TYPE_1__* TableScanDesc ;
struct TYPE_3__ {int /*<<< orphan*/  rs_flags; int /*<<< orphan*/  rs_snapshot; } ;
typedef  int /*<<< orphan*/  Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsMVCCSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SO_TEMP_SNAPSHOT ; 

void
table_scan_update_snapshot(TableScanDesc scan, Snapshot snapshot)
{
	Assert(IsMVCCSnapshot(snapshot));

	RegisterSnapshot(snapshot);
	scan->rs_snapshot = snapshot;
	scan->rs_flags |= SO_TEMP_SNAPSHOT;
}