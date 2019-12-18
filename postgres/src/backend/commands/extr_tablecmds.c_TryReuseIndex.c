#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  oldNode; int /*<<< orphan*/  excludeOpNames; int /*<<< orphan*/  indexParams; int /*<<< orphan*/  accessMethod; } ;
struct TYPE_9__ {int /*<<< orphan*/  relNode; } ;
struct TYPE_10__ {TYPE_2__ rd_node; TYPE_1__* rd_rel; } ;
struct TYPE_8__ {scalar_t__ relkind; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ IndexStmt ;

/* Variables and functions */
 scalar_t__ CheckIndexCompatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 int /*<<< orphan*/  index_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
TryReuseIndex(Oid oldId, IndexStmt *stmt)
{
	if (CheckIndexCompatible(oldId,
							 stmt->accessMethod,
							 stmt->indexParams,
							 stmt->excludeOpNames))
	{
		Relation	irel = index_open(oldId, NoLock);

		/* If it's a partitioned index, there is no storage to share. */
		if (irel->rd_rel->relkind != RELKIND_PARTITIONED_INDEX)
			stmt->oldNode = irel->rd_node.relNode;
		index_close(irel, NoLock);
	}
}