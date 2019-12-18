#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  node; } ;
struct TYPE_8__ {TYPE_1__ smgr_rnode; } ;
struct TYPE_7__ {TYPE_4__* rd_smgr; } ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ Page ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  INIT_FORKNUM ; 
 int /*<<< orphan*/  PageSetChecksumInplace (scalar_t__,int /*<<< orphan*/ ) ; 
 int SPGIST_LEAF ; 
 int /*<<< orphan*/  SPGIST_METAPAGE_BLKNO ; 
 int SPGIST_NULLS ; 
 int /*<<< orphan*/  SPGIST_NULL_BLKNO ; 
 int /*<<< orphan*/  SPGIST_ROOT_BLKNO ; 
 int /*<<< orphan*/  SpGistInitMetapage (scalar_t__) ; 
 int /*<<< orphan*/  SpGistInitPage (scalar_t__,int) ; 
 int /*<<< orphan*/  log_newpage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrimmedsync (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrwrite (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void
spgbuildempty(Relation index)
{
	Page		page;

	/* Construct metapage. */
	page = (Page) palloc(BLCKSZ);
	SpGistInitMetapage(page);

	/*
	 * Write the page and log it unconditionally.  This is important
	 * particularly for indexes created on tablespaces and databases whose
	 * creation happened after the last redo pointer as recovery removes any
	 * of their existing content when the corresponding create records are
	 * replayed.
	 */
	PageSetChecksumInplace(page, SPGIST_METAPAGE_BLKNO);
	smgrwrite(index->rd_smgr, INIT_FORKNUM, SPGIST_METAPAGE_BLKNO,
			  (char *) page, true);
	log_newpage(&index->rd_smgr->smgr_rnode.node, INIT_FORKNUM,
				SPGIST_METAPAGE_BLKNO, page, true);

	/* Likewise for the root page. */
	SpGistInitPage(page, SPGIST_LEAF);

	PageSetChecksumInplace(page, SPGIST_ROOT_BLKNO);
	smgrwrite(index->rd_smgr, INIT_FORKNUM, SPGIST_ROOT_BLKNO,
			  (char *) page, true);
	log_newpage(&index->rd_smgr->smgr_rnode.node, INIT_FORKNUM,
				SPGIST_ROOT_BLKNO, page, true);

	/* Likewise for the null-tuples root page. */
	SpGistInitPage(page, SPGIST_LEAF | SPGIST_NULLS);

	PageSetChecksumInplace(page, SPGIST_NULL_BLKNO);
	smgrwrite(index->rd_smgr, INIT_FORKNUM, SPGIST_NULL_BLKNO,
			  (char *) page, true);
	log_newpage(&index->rd_smgr->smgr_rnode.node, INIT_FORKNUM,
				SPGIST_NULL_BLKNO, page, true);

	/*
	 * An immediate sync is required even if we xlog'd the pages, because the
	 * writes did not go through shared buffers and therefore a concurrent
	 * checkpoint may have moved the redo pointer past our xlog record.
	 */
	smgrimmedsync(index->rd_smgr, INIT_FORKNUM);
}