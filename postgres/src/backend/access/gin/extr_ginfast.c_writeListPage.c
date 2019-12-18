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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32 ;
struct TYPE_4__ {size_t ntuples; scalar_t__ rightlink; } ;
typedef  TYPE_1__ ginxlogInsertListPage ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_6__ {int maxoff; scalar_t__ rightlink; } ;
struct TYPE_5__ {char* data; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__ PGAlignedBlock ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t BLCKSZ ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FirstOffsetNumber ; 
 int /*<<< orphan*/  GIN_LIST ; 
 int /*<<< orphan*/  GinInitBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageSetFullRow (int /*<<< orphan*/ ) ; 
 int IndexTupleSize (scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 size_t PageGetExactFreeSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_GIN_ID ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_GIN_INSERT_LISTPAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 

__attribute__((used)) static int32
writeListPage(Relation index, Buffer buffer,
			  IndexTuple *tuples, int32 ntuples, BlockNumber rightlink)
{
	Page		page = BufferGetPage(buffer);
	int32		i,
				freesize,
				size = 0;
	OffsetNumber l,
				off;
	PGAlignedBlock workspace;
	char	   *ptr;

	START_CRIT_SECTION();

	GinInitBuffer(buffer, GIN_LIST);

	off = FirstOffsetNumber;
	ptr = workspace.data;

	for (i = 0; i < ntuples; i++)
	{
		int			this_size = IndexTupleSize(tuples[i]);

		memcpy(ptr, tuples[i], this_size);
		ptr += this_size;
		size += this_size;

		l = PageAddItem(page, (Item) tuples[i], this_size, off, false, false);

		if (l == InvalidOffsetNumber)
			elog(ERROR, "failed to add item to index page in \"%s\"",
				 RelationGetRelationName(index));

		off++;
	}

	Assert(size <= BLCKSZ);		/* else we overran workspace */

	GinPageGetOpaque(page)->rightlink = rightlink;

	/*
	 * tail page may contain only whole row(s) or final part of row placed on
	 * previous pages (a "row" here meaning all the index tuples generated for
	 * one heap tuple)
	 */
	if (rightlink == InvalidBlockNumber)
	{
		GinPageSetFullRow(page);
		GinPageGetOpaque(page)->maxoff = 1;
	}
	else
	{
		GinPageGetOpaque(page)->maxoff = 0;
	}

	MarkBufferDirty(buffer);

	if (RelationNeedsWAL(index))
	{
		ginxlogInsertListPage data;
		XLogRecPtr	recptr;

		data.rightlink = rightlink;
		data.ntuples = ntuples;

		XLogBeginInsert();
		XLogRegisterData((char *) &data, sizeof(ginxlogInsertListPage));

		XLogRegisterBuffer(0, buffer, REGBUF_WILL_INIT);
		XLogRegisterBufData(0, workspace.data, size);

		recptr = XLogInsert(RM_GIN_ID, XLOG_GIN_INSERT_LISTPAGE);
		PageSetLSN(page, recptr);
	}

	/* get free space before releasing buffer */
	freesize = PageGetExactFreeSpace(page);

	UnlockReleaseBuffer(buffer);

	END_CRIT_SECTION();

	return freesize;
}