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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_delete_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pendingReindexedIndexes ; 

__attribute__((used)) static void
RemoveReindexPending(Oid indexOid)
{
	if (IsInParallelMode())
		elog(ERROR, "cannot modify reindex state during a parallel operation");
	pendingReindexedIndexes = list_delete_oid(pendingReindexedIndexes,
											  indexOid);
}