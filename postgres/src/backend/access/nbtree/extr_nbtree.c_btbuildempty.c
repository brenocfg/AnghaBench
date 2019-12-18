#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  node; } ;
struct TYPE_8__ {TYPE_1__ smgr_rnode; } ;
struct TYPE_7__ {TYPE_3__* rd_smgr; } ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ Page ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BTREE_METAPAGE ; 
 int /*<<< orphan*/  INIT_FORKNUM ; 
 int /*<<< orphan*/  P_NONE ; 
 int /*<<< orphan*/  PageSetChecksumInplace (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_initmetapage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_newpage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrimmedsync (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrwrite (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void
btbuildempty(Relation index)
{
	Page		metapage;

	/* Construct metapage. */
	metapage = (Page) palloc(BLCKSZ);
	_bt_initmetapage(metapage, P_NONE, 0);

	/*
	 * Write the page and log it.  It might seem that an immediate sync would
	 * be sufficient to guarantee that the file exists on disk, but recovery
	 * itself might remove it while replaying, for example, an
	 * XLOG_DBASE_CREATE or XLOG_TBLSPC_CREATE record.  Therefore, we need
	 * this even when wal_level=minimal.
	 */
	PageSetChecksumInplace(metapage, BTREE_METAPAGE);
	smgrwrite(index->rd_smgr, INIT_FORKNUM, BTREE_METAPAGE,
			  (char *) metapage, true);
	log_newpage(&index->rd_smgr->smgr_rnode.node, INIT_FORKNUM,
				BTREE_METAPAGE, metapage, true);

	/*
	 * An immediate sync is required even if we xlog'd the page, because the
	 * write did not go through shared_buffers and therefore a concurrent
	 * checkpoint may have moved the redo pointer past our xlog record.
	 */
	smgrimmedsync(index->rd_smgr, INIT_FORKNUM);
}