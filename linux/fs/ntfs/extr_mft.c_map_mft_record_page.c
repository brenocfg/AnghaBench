#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_5__ {unsigned int mft_record_size_bits; unsigned int mft_record_size; int /*<<< orphan*/  sb; struct inode* mft_ino; } ;
typedef  TYPE_1__ ntfs_volume ;
struct TYPE_6__ {unsigned int mft_no; unsigned int page_ofs; struct page* page; TYPE_1__* vol; } ;
typedef  TYPE_2__ ntfs_inode ;
typedef  unsigned int loff_t ;
typedef  int /*<<< orphan*/  le32 ;
typedef  void MFT_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct page*) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  NVolSetErrors (TYPE_1__*) ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int i_size_read (struct inode*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  ntfs_is_mft_recordp (int /*<<< orphan*/ *) ; 
 struct page* ntfs_map_page (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ntfs_unmap_page (struct page*) ; 
 void* page_address (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline MFT_RECORD *map_mft_record_page(ntfs_inode *ni)
{
	loff_t i_size;
	ntfs_volume *vol = ni->vol;
	struct inode *mft_vi = vol->mft_ino;
	struct page *page;
	unsigned long index, end_index;
	unsigned ofs;

	BUG_ON(ni->page);
	/*
	 * The index into the page cache and the offset within the page cache
	 * page of the wanted mft record. FIXME: We need to check for
	 * overflowing the unsigned long, but I don't think we would ever get
	 * here if the volume was that big...
	 */
	index = (u64)ni->mft_no << vol->mft_record_size_bits >>
			PAGE_SHIFT;
	ofs = (ni->mft_no << vol->mft_record_size_bits) & ~PAGE_MASK;

	i_size = i_size_read(mft_vi);
	/* The maximum valid index into the page cache for $MFT's data. */
	end_index = i_size >> PAGE_SHIFT;

	/* If the wanted index is out of bounds the mft record doesn't exist. */
	if (unlikely(index >= end_index)) {
		if (index > end_index || (i_size & ~PAGE_MASK) < ofs +
				vol->mft_record_size) {
			page = ERR_PTR(-ENOENT);
			ntfs_error(vol->sb, "Attempt to read mft record 0x%lx, "
					"which is beyond the end of the mft.  "
					"This is probably a bug in the ntfs "
					"driver.", ni->mft_no);
			goto err_out;
		}
	}
	/* Read, map, and pin the page. */
	page = ntfs_map_page(mft_vi->i_mapping, index);
	if (!IS_ERR(page)) {
		/* Catch multi sector transfer fixup errors. */
		if (likely(ntfs_is_mft_recordp((le32*)(page_address(page) +
				ofs)))) {
			ni->page = page;
			ni->page_ofs = ofs;
			return page_address(page) + ofs;
		}
		ntfs_error(vol->sb, "Mft record 0x%lx is corrupt.  "
				"Run chkdsk.", ni->mft_no);
		ntfs_unmap_page(page);
		page = ERR_PTR(-EIO);
		NVolSetErrors(vol);
	}
err_out:
	ni->page = NULL;
	ni->page_ofs = 0;
	return (void*)page;
}