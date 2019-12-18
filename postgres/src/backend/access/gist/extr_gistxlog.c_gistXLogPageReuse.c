#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  latestRemovedFullXid; int /*<<< orphan*/  block; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ gistxlogPageReuse ;
struct TYPE_5__ {int /*<<< orphan*/  rd_node; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  FullTransactionId ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  RM_GIST_ID ; 
 int /*<<< orphan*/  SizeOfGistxlogPageReuse ; 
 int /*<<< orphan*/  XLOG_GIST_PAGE_REUSE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 

void
gistXLogPageReuse(Relation rel, BlockNumber blkno, FullTransactionId latestRemovedXid)
{
	gistxlogPageReuse xlrec_reuse;

	/*
	 * Note that we don't register the buffer with the record, because this
	 * operation doesn't modify the page. This record only exists to provide a
	 * conflict point for Hot Standby.
	 */

	/* XLOG stuff */
	xlrec_reuse.node = rel->rd_node;
	xlrec_reuse.block = blkno;
	xlrec_reuse.latestRemovedFullXid = latestRemovedXid;

	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec_reuse, SizeOfGistxlogPageReuse);

	XLogInsert(RM_GIST_ID, XLOG_GIST_PAGE_REUSE);
}