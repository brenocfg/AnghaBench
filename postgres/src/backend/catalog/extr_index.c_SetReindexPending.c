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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ list_copy (int /*<<< orphan*/ *) ; 
 scalar_t__ pendingReindexedIndexes ; 

__attribute__((used)) static void
SetReindexPending(List *indexes)
{
	/* Reindexing is not re-entrant. */
	if (pendingReindexedIndexes)
		elog(ERROR, "cannot reindex while reindexing");
	if (IsInParallelMode())
		elog(ERROR, "cannot modify reindex state during a parallel operation");
	pendingReindexedIndexes = list_copy(indexes);
}