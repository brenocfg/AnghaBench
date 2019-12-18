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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BRIN_IS_META_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ BRIN_IS_REVMAP_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordPageWithFreeSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_page_get_freespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_initialize_empty_new_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
brin_page_cleanup(Relation idxrel, Buffer buf)
{
	Page		page = BufferGetPage(buf);

	/*
	 * If a page was left uninitialized, initialize it now; also record it in
	 * FSM.
	 *
	 * Somebody else might be extending the relation concurrently.  To avoid
	 * re-initializing the page before they can grab the buffer lock, we
	 * acquire the extension lock momentarily.  Since they hold the extension
	 * lock from before getting the page and after its been initialized, we're
	 * sure to see their initialization.
	 */
	if (PageIsNew(page))
	{
		LockRelationForExtension(idxrel, ShareLock);
		UnlockRelationForExtension(idxrel, ShareLock);

		LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
		if (PageIsNew(page))
		{
			brin_initialize_empty_new_buffer(idxrel, buf);
			LockBuffer(buf, BUFFER_LOCK_UNLOCK);
			return;
		}
		LockBuffer(buf, BUFFER_LOCK_UNLOCK);
	}

	/* Nothing to be done for non-regular index pages */
	if (BRIN_IS_META_PAGE(BufferGetPage(buf)) ||
		BRIN_IS_REVMAP_PAGE(BufferGetPage(buf)))
		return;

	/* Measure free space and record it */
	RecordPageWithFreeSpace(idxrel, BufferGetBlockNumber(buf),
							br_page_get_freespace(page));
}