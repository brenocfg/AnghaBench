#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* rd_rel; int /*<<< orphan*/  rd_smgr; int /*<<< orphan*/  rd_backend; } ;
struct TYPE_7__ {int /*<<< orphan*/  relpersistence; } ;
typedef  int /*<<< orphan*/  SMgrRelation ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  scalar_t__ ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  FlushRelationBuffers (TYPE_2__*) ; 
 scalar_t__ INIT_FORKNUM ; 
 scalar_t__ MAIN_FORKNUM ; 
 scalar_t__ MAX_FORKNUM ; 
 int /*<<< orphan*/  RELPERSISTENCE_PERMANENT ; 
 int /*<<< orphan*/  RELPERSISTENCE_UNLOGGED ; 
 int /*<<< orphan*/  RelationCopyStorage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationCreateStorage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationDropStorage (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_2__*) ; 
 int /*<<< orphan*/  log_smgrcreate (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  smgrclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrcreate (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ smgrexists (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  smgropen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
index_copy_data(Relation rel, RelFileNode newrnode)
{
	SMgrRelation dstrel;

	dstrel = smgropen(newrnode, rel->rd_backend);
	RelationOpenSmgr(rel);

	/*
	 * Since we copy the file directly without looking at the shared buffers,
	 * we'd better first flush out any pages of the source relation that are
	 * in shared buffers.  We assume no new changes will be made while we are
	 * holding exclusive lock on the rel.
	 */
	FlushRelationBuffers(rel);

	/*
	 * Create and copy all forks of the relation, and schedule unlinking of
	 * old physical files.
	 *
	 * NOTE: any conflict in relfilenode value will be caught in
	 * RelationCreateStorage().
	 */
	RelationCreateStorage(newrnode, rel->rd_rel->relpersistence);

	/* copy main fork */
	RelationCopyStorage(rel->rd_smgr, dstrel, MAIN_FORKNUM,
						rel->rd_rel->relpersistence);

	/* copy those extra forks that exist */
	for (ForkNumber forkNum = MAIN_FORKNUM + 1;
		 forkNum <= MAX_FORKNUM; forkNum++)
	{
		if (smgrexists(rel->rd_smgr, forkNum))
		{
			smgrcreate(dstrel, forkNum, false);

			/*
			 * WAL log creation if the relation is persistent, or this is the
			 * init fork of an unlogged relation.
			 */
			if (rel->rd_rel->relpersistence == RELPERSISTENCE_PERMANENT ||
				(rel->rd_rel->relpersistence == RELPERSISTENCE_UNLOGGED &&
				 forkNum == INIT_FORKNUM))
				log_smgrcreate(&newrnode, forkNum);
			RelationCopyStorage(rel->rd_smgr, dstrel, forkNum,
								rel->rd_rel->relpersistence);
		}
	}

	/* drop old relation, and close new one */
	RelationDropStorage(rel);
	smgrclose(dstrel);
}