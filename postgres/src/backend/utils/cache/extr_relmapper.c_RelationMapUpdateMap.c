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
typedef  int /*<<< orphan*/  RelMapFile ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int GetCurrentTransactionNestLevel () ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  active_local_updates ; 
 int /*<<< orphan*/  active_shared_updates ; 
 int /*<<< orphan*/  apply_map_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  local_map ; 
 int /*<<< orphan*/  pending_local_updates ; 
 int /*<<< orphan*/  pending_shared_updates ; 
 int /*<<< orphan*/  shared_map ; 

void
RelationMapUpdateMap(Oid relationId, Oid fileNode, bool shared,
					 bool immediate)
{
	RelMapFile *map;

	if (IsBootstrapProcessingMode())
	{
		/*
		 * In bootstrap mode, the mapping gets installed in permanent map.
		 */
		if (shared)
			map = &shared_map;
		else
			map = &local_map;
	}
	else
	{
		/*
		 * We don't currently support map changes within subtransactions, or
		 * when in parallel mode.  This could be done with more bookkeeping
		 * infrastructure, but it doesn't presently seem worth it.
		 */
		if (GetCurrentTransactionNestLevel() > 1)
			elog(ERROR, "cannot change relation mapping within subtransaction");

		if (IsInParallelMode())
			elog(ERROR, "cannot change relation mapping in parallel mode");

		if (immediate)
		{
			/* Make it active, but only locally */
			if (shared)
				map = &active_shared_updates;
			else
				map = &active_local_updates;
		}
		else
		{
			/* Make it pending */
			if (shared)
				map = &pending_shared_updates;
			else
				map = &pending_local_updates;
		}
	}
	apply_map_update(map, relationId, fileNode, true);
}