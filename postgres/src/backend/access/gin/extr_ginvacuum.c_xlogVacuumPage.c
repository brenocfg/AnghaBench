#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageIsData (int /*<<< orphan*/ ) ; 
 int GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_FORCE_IMAGE ; 
 int REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_GIN_ID ; 
 int /*<<< orphan*/  RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_GIN_VACUUM_PAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xlogVacuumPage(Relation index, Buffer buffer)
{
	Page		page = BufferGetPage(buffer);
	XLogRecPtr	recptr;

	/* This is only used for entry tree leaf pages. */
	Assert(!GinPageIsData(page));
	Assert(GinPageIsLeaf(page));

	if (!RelationNeedsWAL(index))
		return;

	/*
	 * Always create a full image, we don't track the changes on the page at
	 * any more fine-grained level. This could obviously be improved...
	 */
	XLogBeginInsert();
	XLogRegisterBuffer(0, buffer, REGBUF_FORCE_IMAGE | REGBUF_STANDARD);

	recptr = XLogInsert(RM_GIN_ID, XLOG_GIN_VACUUM_PAGE);
	PageSetLSN(page, recptr);
}