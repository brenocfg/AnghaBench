#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* smgr_unlink ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* smgr_close ) (TYPE_1__*,scalar_t__) ;} ;
struct TYPE_5__ {int smgr_which; int /*<<< orphan*/  smgr_rnode; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  int /*<<< orphan*/  RelFileNodeBackend ;
typedef  scalar_t__ ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CacheInvalidateSmgr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DropRelFileNodesAllBuffers (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InvalidForkNumber ; 
 scalar_t__ MAX_FORKNUM ; 
 TYPE_3__* smgrsw ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
smgrdounlink(SMgrRelation reln, bool isRedo)
{
	RelFileNodeBackend rnode = reln->smgr_rnode;
	int			which = reln->smgr_which;
	ForkNumber	forknum;

	/* Close the forks at smgr level */
	for (forknum = 0; forknum <= MAX_FORKNUM; forknum++)
		smgrsw[which].smgr_close(reln, forknum);

	/*
	 * Get rid of any remaining buffers for the relation.  bufmgr will just
	 * drop them without bothering to write the contents.
	 */
	DropRelFileNodesAllBuffers(&rnode, 1);

	/*
	 * It'd be nice to tell the stats collector to forget it immediately, too.
	 * But we can't because we don't know the OID (and in cases involving
	 * relfilenode swaps, it's not always clear which table OID to forget,
	 * anyway).
	 */

	/*
	 * Send a shared-inval message to force other backends to close any
	 * dangling smgr references they may have for this rel.  We should do this
	 * before starting the actual unlinking, in case we fail partway through
	 * that step.  Note that the sinval message will eventually come back to
	 * this backend, too, and thereby provide a backstop that we closed our
	 * own smgr rel.
	 */
	CacheInvalidateSmgr(rnode);

	/*
	 * Delete the physical file(s).
	 *
	 * Note: smgr_unlink must treat deletion failure as a WARNING, not an
	 * ERROR, because we've already decided to commit or abort the current
	 * xact.
	 */
	smgrsw[which].smgr_unlink(rnode, InvalidForkNumber, isRedo);
}