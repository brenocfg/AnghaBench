#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ smgr_fsm_nblocks; } ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_11__ {TYPE_3__* rd_smgr; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__ PGAlignedBlock ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  FSM_FORKNUM ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  LockRelationForExtension (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetChecksumInplace (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockRelationForExtension (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrcreate (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smgrexists (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrextend (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ smgrnblocks (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fsm_extend(Relation rel, BlockNumber fsm_nblocks)
{
	BlockNumber fsm_nblocks_now;
	PGAlignedBlock pg;

	PageInit((Page) pg.data, BLCKSZ, 0);

	/*
	 * We use the relation extension lock to lock out other backends trying to
	 * extend the FSM at the same time. It also locks out extension of the
	 * main fork, unnecessarily, but extending the FSM happens seldom enough
	 * that it doesn't seem worthwhile to have a separate lock tag type for
	 * it.
	 *
	 * Note that another backend might have extended or created the relation
	 * by the time we get the lock.
	 */
	LockRelationForExtension(rel, ExclusiveLock);

	/* Might have to re-open if a cache flush happened */
	RelationOpenSmgr(rel);

	/*
	 * Create the FSM file first if it doesn't exist.  If smgr_fsm_nblocks is
	 * positive then it must exist, no need for an smgrexists call.
	 */
	if ((rel->rd_smgr->smgr_fsm_nblocks == 0 ||
		 rel->rd_smgr->smgr_fsm_nblocks == InvalidBlockNumber) &&
		!smgrexists(rel->rd_smgr, FSM_FORKNUM))
		smgrcreate(rel->rd_smgr, FSM_FORKNUM, false);

	fsm_nblocks_now = smgrnblocks(rel->rd_smgr, FSM_FORKNUM);

	while (fsm_nblocks_now < fsm_nblocks)
	{
		PageSetChecksumInplace((Page) pg.data, fsm_nblocks_now);

		smgrextend(rel->rd_smgr, FSM_FORKNUM, fsm_nblocks_now,
				   pg.data, false);
		fsm_nblocks_now++;
	}

	/* Update local cache with the up-to-date size */
	rel->rd_smgr->smgr_fsm_nblocks = fsm_nblocks_now;

	UnlockRelationForExtension(rel, ExclusiveLock);
}