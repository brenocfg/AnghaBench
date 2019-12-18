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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_8__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
struct TYPE_7__ {scalar_t__ hasho_nextblkno; int /*<<< orphan*/  hasho_bucket; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_tid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__* HashPageOpaque ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_3__ HASHCTL ;
typedef  scalar_t__ Buffer ;
typedef  int /*<<< orphan*/  Bucket ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BlockNumberIsValid (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  ConditionalLockBufferForCleanup (scalar_t__) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ FirstOffsetNumber ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_READ ; 
 scalar_t__ InvalidBuffer ; 
 int LH_BUCKET_PAGE ; 
 int LH_OVERFLOW_PAGE ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_dropbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ _hash_get_newblock_from_oldbucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _hash_getbuf (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _hash_splitbucket (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void
_hash_finish_split(Relation rel, Buffer metabuf, Buffer obuf, Bucket obucket,
				   uint32 maxbucket, uint32 highmask, uint32 lowmask)
{
	HASHCTL		hash_ctl;
	HTAB	   *tidhtab;
	Buffer		bucket_nbuf = InvalidBuffer;
	Buffer		nbuf;
	Page		npage;
	BlockNumber nblkno;
	BlockNumber bucket_nblkno;
	HashPageOpaque npageopaque;
	Bucket		nbucket;
	bool		found;

	/* Initialize hash tables used to track TIDs */
	memset(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(ItemPointerData);
	hash_ctl.entrysize = sizeof(ItemPointerData);
	hash_ctl.hcxt = CurrentMemoryContext;

	tidhtab =
		hash_create("bucket ctids",
					256,		/* arbitrary initial size */
					&hash_ctl,
					HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);

	bucket_nblkno = nblkno = _hash_get_newblock_from_oldbucket(rel, obucket);

	/*
	 * Scan the new bucket and build hash table of TIDs
	 */
	for (;;)
	{
		OffsetNumber noffnum;
		OffsetNumber nmaxoffnum;

		nbuf = _hash_getbuf(rel, nblkno, HASH_READ,
							LH_BUCKET_PAGE | LH_OVERFLOW_PAGE);

		/* remember the primary bucket buffer to acquire cleanup lock on it. */
		if (nblkno == bucket_nblkno)
			bucket_nbuf = nbuf;

		npage = BufferGetPage(nbuf);
		npageopaque = (HashPageOpaque) PageGetSpecialPointer(npage);

		/* Scan each tuple in new page */
		nmaxoffnum = PageGetMaxOffsetNumber(npage);
		for (noffnum = FirstOffsetNumber;
			 noffnum <= nmaxoffnum;
			 noffnum = OffsetNumberNext(noffnum))
		{
			IndexTuple	itup;

			/* Fetch the item's TID and insert it in hash table. */
			itup = (IndexTuple) PageGetItem(npage,
											PageGetItemId(npage, noffnum));

			(void) hash_search(tidhtab, &itup->t_tid, HASH_ENTER, &found);

			Assert(!found);
		}

		nblkno = npageopaque->hasho_nextblkno;

		/*
		 * release our write lock without modifying buffer and ensure to
		 * retain the pin on primary bucket.
		 */
		if (nbuf == bucket_nbuf)
			LockBuffer(nbuf, BUFFER_LOCK_UNLOCK);
		else
			_hash_relbuf(rel, nbuf);

		/* Exit loop if no more overflow pages in new bucket */
		if (!BlockNumberIsValid(nblkno))
			break;
	}

	/*
	 * Conditionally get the cleanup lock on old and new buckets to perform
	 * the split operation.  If we don't get the cleanup locks, silently give
	 * up and next insertion on old bucket will try again to complete the
	 * split.
	 */
	if (!ConditionalLockBufferForCleanup(obuf))
	{
		hash_destroy(tidhtab);
		return;
	}
	if (!ConditionalLockBufferForCleanup(bucket_nbuf))
	{
		LockBuffer(obuf, BUFFER_LOCK_UNLOCK);
		hash_destroy(tidhtab);
		return;
	}

	npage = BufferGetPage(bucket_nbuf);
	npageopaque = (HashPageOpaque) PageGetSpecialPointer(npage);
	nbucket = npageopaque->hasho_bucket;

	_hash_splitbucket(rel, metabuf, obucket,
					  nbucket, obuf, bucket_nbuf, tidhtab,
					  maxbucket, highmask, lowmask);

	_hash_dropbuf(rel, bucket_nbuf);
	hash_destroy(tidhtab);
}