#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int atCommit; struct TYPE_10__* next; int /*<<< orphan*/  nestLevel; int /*<<< orphan*/  backend; int /*<<< orphan*/  relnode; } ;
struct TYPE_8__ {int /*<<< orphan*/  node; } ;
struct TYPE_9__ {TYPE_1__ smgr_rnode; } ;
typedef  TYPE_2__* SMgrRelation ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  TYPE_3__ PendingRelDelete ;
typedef  int /*<<< orphan*/  BackendId ;

/* Variables and functions */
 int /*<<< orphan*/  BackendIdForTempRelations () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentTransactionNestLevel () ; 
 int /*<<< orphan*/  InvalidBackendId ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
#define  RELPERSISTENCE_PERMANENT 130 
#define  RELPERSISTENCE_TEMP 129 
#define  RELPERSISTENCE_UNLOGGED 128 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  log_smgrcreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* pendingDeletes ; 
 int /*<<< orphan*/  smgrcreate (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* smgropen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SMgrRelation
RelationCreateStorage(RelFileNode rnode, char relpersistence)
{
	PendingRelDelete *pending;
	SMgrRelation srel;
	BackendId	backend;
	bool		needs_wal;

	switch (relpersistence)
	{
		case RELPERSISTENCE_TEMP:
			backend = BackendIdForTempRelations();
			needs_wal = false;
			break;
		case RELPERSISTENCE_UNLOGGED:
			backend = InvalidBackendId;
			needs_wal = false;
			break;
		case RELPERSISTENCE_PERMANENT:
			backend = InvalidBackendId;
			needs_wal = true;
			break;
		default:
			elog(ERROR, "invalid relpersistence: %c", relpersistence);
			return NULL;		/* placate compiler */
	}

	srel = smgropen(rnode, backend);
	smgrcreate(srel, MAIN_FORKNUM, false);

	if (needs_wal)
		log_smgrcreate(&srel->smgr_rnode.node, MAIN_FORKNUM);

	/* Add the relation to the list of stuff to delete at abort */
	pending = (PendingRelDelete *)
		MemoryContextAlloc(TopMemoryContext, sizeof(PendingRelDelete));
	pending->relnode = rnode;
	pending->backend = backend;
	pending->atCommit = false;	/* delete if abort */
	pending->nestLevel = GetCurrentTransactionNestLevel();
	pending->next = pendingDeletes;
	pendingDeletes = pending;

	return srel;
}