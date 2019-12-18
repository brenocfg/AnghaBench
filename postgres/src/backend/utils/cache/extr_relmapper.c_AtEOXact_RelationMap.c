#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ num_mappings; } ;
struct TYPE_7__ {scalar_t__ num_mappings; } ;
struct TYPE_6__ {scalar_t__ num_mappings; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__ active_local_updates ; 
 TYPE_1__ active_shared_updates ; 
 TYPE_3__ pending_local_updates ; 
 TYPE_2__ pending_shared_updates ; 
 int /*<<< orphan*/  perform_relmap_update (int,TYPE_1__*) ; 

void
AtEOXact_RelationMap(bool isCommit, bool isParallelWorker)
{
	if (isCommit && !isParallelWorker)
	{
		/*
		 * We should not get here with any "pending" updates.  (We could
		 * logically choose to treat such as committed, but in the current
		 * code this should never happen.)
		 */
		Assert(pending_shared_updates.num_mappings == 0);
		Assert(pending_local_updates.num_mappings == 0);

		/*
		 * Write any active updates to the actual map files, then reset them.
		 */
		if (active_shared_updates.num_mappings != 0)
		{
			perform_relmap_update(true, &active_shared_updates);
			active_shared_updates.num_mappings = 0;
		}
		if (active_local_updates.num_mappings != 0)
		{
			perform_relmap_update(false, &active_local_updates);
			active_local_updates.num_mappings = 0;
		}
	}
	else
	{
		/* Abort or parallel worker --- drop all local and pending updates */
		Assert(!isParallelWorker || pending_shared_updates.num_mappings == 0);
		Assert(!isParallelWorker || pending_local_updates.num_mappings == 0);

		active_shared_updates.num_mappings = 0;
		active_local_updates.num_mappings = 0;
		pending_shared_updates.num_mappings = 0;
		pending_local_updates.num_mappings = 0;
	}
}