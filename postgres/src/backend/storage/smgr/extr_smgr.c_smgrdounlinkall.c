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
struct TYPE_6__ {int /*<<< orphan*/  (* smgr_unlink ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* smgr_close ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int smgr_which; int /*<<< orphan*/  smgr_rnode; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  int /*<<< orphan*/  RelFileNodeBackend ;
typedef  int /*<<< orphan*/  ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CacheInvalidateSmgr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DropRelFileNodesAllBuffers (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MAX_FORKNUM ; 
 int /*<<< orphan*/ * palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 TYPE_3__* smgrsw ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
smgrdounlinkall(SMgrRelation *rels, int nrels, bool isRedo)
{
	int			i = 0;
	RelFileNodeBackend *rnodes;
	ForkNumber	forknum;

	if (nrels == 0)
		return;

	/*
	 * create an array which contains all relations to be dropped, and close
	 * each relation's forks at the smgr level while at it
	 */
	rnodes = palloc(sizeof(RelFileNodeBackend) * nrels);
	for (i = 0; i < nrels; i++)
	{
		RelFileNodeBackend rnode = rels[i]->smgr_rnode;
		int			which = rels[i]->smgr_which;

		rnodes[i] = rnode;

		/* Close the forks at smgr level */
		for (forknum = 0; forknum <= MAX_FORKNUM; forknum++)
			smgrsw[which].smgr_close(rels[i], forknum);
	}

	/*
	 * Get rid of any remaining buffers for the relations.  bufmgr will just
	 * drop them without bothering to write the contents.
	 */
	DropRelFileNodesAllBuffers(rnodes, nrels);

	/*
	 * It'd be nice to tell the stats collector to forget them immediately,
	 * too. But we can't because we don't know the OIDs.
	 */

	/*
	 * Send a shared-inval message to force other backends to close any
	 * dangling smgr references they may have for these rels.  We should do
	 * this before starting the actual unlinking, in case we fail partway
	 * through that step.  Note that the sinval messages will eventually come
	 * back to this backend, too, and thereby provide a backstop that we
	 * closed our own smgr rel.
	 */
	for (i = 0; i < nrels; i++)
		CacheInvalidateSmgr(rnodes[i]);

	/*
	 * Delete the physical file(s).
	 *
	 * Note: smgr_unlink must treat deletion failure as a WARNING, not an
	 * ERROR, because we've already decided to commit or abort the current
	 * xact.
	 */

	for (i = 0; i < nrels; i++)
	{
		int			which = rels[i]->smgr_which;

		for (forknum = 0; forknum <= MAX_FORKNUM; forknum++)
			smgrsw[which].smgr_unlink(rnodes[i], forknum, isRedo);
	}

	pfree(rnodes);
}