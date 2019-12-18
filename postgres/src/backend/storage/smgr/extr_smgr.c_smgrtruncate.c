#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* smgr_truncate ) (TYPE_1__*,scalar_t__,void*) ;} ;
struct TYPE_5__ {size_t smgr_which; void* smgr_vm_nblocks; void* smgr_fsm_nblocks; int /*<<< orphan*/  smgr_rnode; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  scalar_t__ ForkNumber ;
typedef  void* BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CacheInvalidateSmgr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DropRelFileNodeBuffers (int /*<<< orphan*/ ,scalar_t__*,int,void**) ; 
 scalar_t__ FSM_FORKNUM ; 
 scalar_t__ VISIBILITYMAP_FORKNUM ; 
 TYPE_4__* smgrsw ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__,void*) ; 

void
smgrtruncate(SMgrRelation reln, ForkNumber *forknum, int nforks, BlockNumber *nblocks)
{
	int		i;

	/*
	 * Get rid of any buffers for the about-to-be-deleted blocks. bufmgr will
	 * just drop them without bothering to write the contents.
	 */
	DropRelFileNodeBuffers(reln->smgr_rnode, forknum, nforks, nblocks);

	/*
	 * Send a shared-inval message to force other backends to close any smgr
	 * references they may have for this rel.  This is useful because they
	 * might have open file pointers to segments that got removed, and/or
	 * smgr_targblock variables pointing past the new rel end.  (The inval
	 * message will come back to our backend, too, causing a
	 * probably-unnecessary local smgr flush.  But we don't expect that this
	 * is a performance-critical path.)  As in the unlink code, we want to be
	 * sure the message is sent before we start changing things on-disk.
	 */
	CacheInvalidateSmgr(reln->smgr_rnode);

	/* Do the truncation */
	for (i = 0; i < nforks; i++)
	{
		smgrsw[reln->smgr_which].smgr_truncate(reln, forknum[i], nblocks[i]);

		/*
		 * We might as well update the local smgr_fsm_nblocks and
		 * smgr_vm_nblocks settings. The smgr cache inval message that
		 * this function sent will cause other backends to invalidate
		 * their copies of smgr_fsm_nblocks and smgr_vm_nblocks,
		 * and these ones too at the next command boundary.
		 * But these ensure they aren't outright wrong until then.
		 */
		if (forknum[i] == FSM_FORKNUM)
			reln->smgr_fsm_nblocks = nblocks[i];
		if (forknum[i] == VISIBILITYMAP_FORKNUM)
			reln->smgr_vm_nblocks = nblocks[i];
	}
}