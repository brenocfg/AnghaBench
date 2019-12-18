#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* rd_tableam; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* parallelscan_estimate ) (TYPE_2__*) ;} ;
typedef  scalar_t__ Snapshot ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  EstimateSnapshotSpace (scalar_t__) ; 
 scalar_t__ IsMVCCSnapshot (scalar_t__) ; 
 scalar_t__ SnapshotAny ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

Size
table_parallelscan_estimate(Relation rel, Snapshot snapshot)
{
	Size		sz = 0;

	if (IsMVCCSnapshot(snapshot))
		sz = add_size(sz, EstimateSnapshotSpace(snapshot));
	else
		Assert(snapshot == SnapshotAny);

	sz = add_size(sz, rel->rd_tableam->parallelscan_estimate(rel));

	return sz;
}