#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; int /*<<< orphan*/  mrec_lock; int /*<<< orphan*/  mft_no; struct page* page; } ;
typedef  TYPE_1__ ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntfs_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_mft_record_page (TYPE_1__*) ; 

void unmap_mft_record(ntfs_inode *ni)
{
	struct page *page = ni->page;

	BUG_ON(!page);

	ntfs_debug("Entering for mft_no 0x%lx.", ni->mft_no);

	unmap_mft_record_page(ni);
	mutex_unlock(&ni->mrec_lock);
	atomic_dec(&ni->count);
	/*
	 * If pure ntfs_inode, i.e. no vfs inode attached, we leave it to
	 * ntfs_clear_extent_inode() in the extent inode case, and to the
	 * caller in the non-extent, yet pure ntfs inode case, to do the actual
	 * tear down of all structures and freeing of all allocated memory.
	 */
	return;
}