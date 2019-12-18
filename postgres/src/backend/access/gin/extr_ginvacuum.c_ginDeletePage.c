#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ rightLink; int /*<<< orphan*/  deleteXid; int /*<<< orphan*/  parentOffset; } ;
typedef  TYPE_2__ ginxlogDeletePage ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_9__ {scalar_t__ rightlink; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_1__* result; int /*<<< orphan*/  index; int /*<<< orphan*/  strategy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pages_deleted; } ;
typedef  int /*<<< orphan*/  PostingItem ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_3__ GinVacuumState ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  GIN_DELETED ; 
 int /*<<< orphan*/  GIN_EXCLUSIVE ; 
 int /*<<< orphan*/ * GinDataPageGetPostingItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageDeletePostingItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageGetDeleteXid (int /*<<< orphan*/ ) ; 
 TYPE_5__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageSetDeleteXid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PostingItemGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PredicateLockPageCombine (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_GIN_ID ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadNewTransactionId () ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_GIN_DELETE_PAGE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 

__attribute__((used)) static void
ginDeletePage(GinVacuumState *gvs, BlockNumber deleteBlkno, BlockNumber leftBlkno,
			  BlockNumber parentBlkno, OffsetNumber myoff, bool isParentRoot)
{
	Buffer		dBuffer;
	Buffer		lBuffer;
	Buffer		pBuffer;
	Page		page,
				parentPage;
	BlockNumber rightlink;

	/*
	 * This function MUST be called only if someone of parent pages hold
	 * exclusive cleanup lock. This guarantees that no insertions currently
	 * happen in this subtree. Caller also acquire Exclusive lock on deletable
	 * page and is acquiring and releasing exclusive lock on left page before.
	 * Left page was locked and released. Then parent and this page are
	 * locked. We acquire left page lock here only to mark page dirty after
	 * changing right pointer.
	 */
	lBuffer = ReadBufferExtended(gvs->index, MAIN_FORKNUM, leftBlkno,
								 RBM_NORMAL, gvs->strategy);
	dBuffer = ReadBufferExtended(gvs->index, MAIN_FORKNUM, deleteBlkno,
								 RBM_NORMAL, gvs->strategy);
	pBuffer = ReadBufferExtended(gvs->index, MAIN_FORKNUM, parentBlkno,
								 RBM_NORMAL, gvs->strategy);

	LockBuffer(lBuffer, GIN_EXCLUSIVE);

	page = BufferGetPage(dBuffer);
	rightlink = GinPageGetOpaque(page)->rightlink;

	/* For deleted page remember last xid which could knew its address */
	GinPageSetDeleteXid(page, ReadNewTransactionId());

	/*
	 * Any insert which would have gone on the leaf block will now go to its
	 * right sibling.
	 */
	PredicateLockPageCombine(gvs->index, deleteBlkno, rightlink);

	START_CRIT_SECTION();

	/* Unlink the page by changing left sibling's rightlink */
	page = BufferGetPage(lBuffer);
	GinPageGetOpaque(page)->rightlink = rightlink;

	/* Delete downlink from parent */
	parentPage = BufferGetPage(pBuffer);
#ifdef USE_ASSERT_CHECKING
	do
	{
		PostingItem *tod = GinDataPageGetPostingItem(parentPage, myoff);

		Assert(PostingItemGetBlockNumber(tod) == deleteBlkno);
	} while (0);
#endif
	GinPageDeletePostingItem(parentPage, myoff);

	page = BufferGetPage(dBuffer);

	/*
	 * we shouldn't change rightlink field to save workability of running
	 * search scan
	 */
	GinPageGetOpaque(page)->flags = GIN_DELETED;

	MarkBufferDirty(pBuffer);
	MarkBufferDirty(lBuffer);
	MarkBufferDirty(dBuffer);

	if (RelationNeedsWAL(gvs->index))
	{
		XLogRecPtr	recptr;
		ginxlogDeletePage data;

		/*
		 * We can't pass REGBUF_STANDARD for the deleted page, because we
		 * didn't set pd_lower on pre-9.4 versions. The page might've been
		 * binary-upgraded from an older version, and hence not have pd_lower
		 * set correctly. Ditto for the left page, but removing the item from
		 * the parent updated its pd_lower, so we know that's OK at this
		 * point.
		 */
		XLogBeginInsert();
		XLogRegisterBuffer(0, dBuffer, 0);
		XLogRegisterBuffer(1, pBuffer, REGBUF_STANDARD);
		XLogRegisterBuffer(2, lBuffer, 0);

		data.parentOffset = myoff;
		data.rightLink = GinPageGetOpaque(page)->rightlink;
		data.deleteXid = GinPageGetDeleteXid(page);

		XLogRegisterData((char *) &data, sizeof(ginxlogDeletePage));

		recptr = XLogInsert(RM_GIN_ID, XLOG_GIN_DELETE_PAGE);
		PageSetLSN(page, recptr);
		PageSetLSN(parentPage, recptr);
		PageSetLSN(BufferGetPage(lBuffer), recptr);
	}

	ReleaseBuffer(pBuffer);
	UnlockReleaseBuffer(lBuffer);
	ReleaseBuffer(dBuffer);

	END_CRIT_SECTION();

	gvs->result->pages_deleted++;
}