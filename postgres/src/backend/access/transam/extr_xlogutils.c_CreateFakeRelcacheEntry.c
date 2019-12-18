#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  relpersistence; } ;
struct TYPE_16__ {TYPE_1__ pgc; } ;
struct TYPE_15__ {int relNode; int /*<<< orphan*/  dbNode; } ;
struct TYPE_12__ {int relId; int /*<<< orphan*/  dbId; } ;
struct TYPE_13__ {TYPE_2__ lockRelId; } ;
struct TYPE_14__ {int /*<<< orphan*/ * rd_smgr; TYPE_3__ rd_lockInfo; TYPE_1__* rd_rel; int /*<<< orphan*/  rd_backend; TYPE_5__ rd_node; } ;
typedef  TYPE_4__* Relation ;
typedef  TYPE_5__ RelFileNode ;
typedef  int /*<<< orphan*/  FakeRelCacheEntryData ;
typedef  TYPE_6__* FakeRelCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InRecovery ; 
 int /*<<< orphan*/  InvalidBackendId ; 
 int /*<<< orphan*/  RELPERSISTENCE_PERMANENT ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_4__*) ; 
 TYPE_6__* palloc0 (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

Relation
CreateFakeRelcacheEntry(RelFileNode rnode)
{
	FakeRelCacheEntry fakeentry;
	Relation	rel;

	Assert(InRecovery);

	/* Allocate the Relation struct and all related space in one block. */
	fakeentry = palloc0(sizeof(FakeRelCacheEntryData));
	rel = (Relation) fakeentry;

	rel->rd_rel = &fakeentry->pgc;
	rel->rd_node = rnode;
	/* We will never be working with temp rels during recovery */
	rel->rd_backend = InvalidBackendId;

	/* It must be a permanent table if we're in recovery. */
	rel->rd_rel->relpersistence = RELPERSISTENCE_PERMANENT;

	/* We don't know the name of the relation; use relfilenode instead */
	sprintf(RelationGetRelationName(rel), "%u", rnode.relNode);

	/*
	 * We set up the lockRelId in case anything tries to lock the dummy
	 * relation.  Note that this is fairly bogus since relNode may be
	 * different from the relation's OID.  It shouldn't really matter though,
	 * since we are presumably running by ourselves and can't have any lock
	 * conflicts ...
	 */
	rel->rd_lockInfo.lockRelId.dbId = rnode.dbNode;
	rel->rd_lockInfo.lockRelId.relId = rnode.relNode;

	rel->rd_smgr = NULL;

	return rel;
}