#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {int ra_pages; } ;
struct file {int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_mode; TYPE_1__ f_ra; struct address_space* f_mapping; } ;
struct backing_dev_info {int ra_pages; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESPIPE ; 
 int /*<<< orphan*/  FMODE_RANDOM ; 
 scalar_t__ IS_DAX (struct inode*) ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  POSIX_FADV_DONTNEED 133 
#define  POSIX_FADV_NOREUSE 132 
#define  POSIX_FADV_NORMAL 131 
#define  POSIX_FADV_RANDOM 130 
#define  POSIX_FADV_SEQUENTIAL 129 
#define  POSIX_FADV_WILLNEED 128 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WB_SYNC_NONE ; 
 int /*<<< orphan*/  __filemap_fdatawrite_range (struct address_space*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  force_page_cache_readahead (struct address_space*,struct file*,scalar_t__,unsigned long) ; 
 struct backing_dev_info* inode_to_bdi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_write_congested (int /*<<< orphan*/ ) ; 
 unsigned long invalidate_mapping_pages (struct address_space*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  lru_add_drain_all () ; 
 struct backing_dev_info noop_backing_dev_info ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int generic_fadvise(struct file *file, loff_t offset, loff_t len, int advice)
{
	struct inode *inode;
	struct address_space *mapping;
	struct backing_dev_info *bdi;
	loff_t endbyte;			/* inclusive */
	pgoff_t start_index;
	pgoff_t end_index;
	unsigned long nrpages;

	inode = file_inode(file);
	if (S_ISFIFO(inode->i_mode))
		return -ESPIPE;

	mapping = file->f_mapping;
	if (!mapping || len < 0)
		return -EINVAL;

	bdi = inode_to_bdi(mapping->host);

	if (IS_DAX(inode) || (bdi == &noop_backing_dev_info)) {
		switch (advice) {
		case POSIX_FADV_NORMAL:
		case POSIX_FADV_RANDOM:
		case POSIX_FADV_SEQUENTIAL:
		case POSIX_FADV_WILLNEED:
		case POSIX_FADV_NOREUSE:
		case POSIX_FADV_DONTNEED:
			/* no bad return value, but ignore advice */
			break;
		default:
			return -EINVAL;
		}
		return 0;
	}

	/*
	 * Careful about overflows. Len == 0 means "as much as possible".  Use
	 * unsigned math because signed overflows are undefined and UBSan
	 * complains.
	 */
	endbyte = (u64)offset + (u64)len;
	if (!len || endbyte < len)
		endbyte = -1;
	else
		endbyte--;		/* inclusive */

	switch (advice) {
	case POSIX_FADV_NORMAL:
		file->f_ra.ra_pages = bdi->ra_pages;
		spin_lock(&file->f_lock);
		file->f_mode &= ~FMODE_RANDOM;
		spin_unlock(&file->f_lock);
		break;
	case POSIX_FADV_RANDOM:
		spin_lock(&file->f_lock);
		file->f_mode |= FMODE_RANDOM;
		spin_unlock(&file->f_lock);
		break;
	case POSIX_FADV_SEQUENTIAL:
		file->f_ra.ra_pages = bdi->ra_pages * 2;
		spin_lock(&file->f_lock);
		file->f_mode &= ~FMODE_RANDOM;
		spin_unlock(&file->f_lock);
		break;
	case POSIX_FADV_WILLNEED:
		/* First and last PARTIAL page! */
		start_index = offset >> PAGE_SHIFT;
		end_index = endbyte >> PAGE_SHIFT;

		/* Careful about overflow on the "+1" */
		nrpages = end_index - start_index + 1;
		if (!nrpages)
			nrpages = ~0UL;

		/*
		 * Ignore return value because fadvise() shall return
		 * success even if filesystem can't retrieve a hint,
		 */
		force_page_cache_readahead(mapping, file, start_index, nrpages);
		break;
	case POSIX_FADV_NOREUSE:
		break;
	case POSIX_FADV_DONTNEED:
		if (!inode_write_congested(mapping->host))
			__filemap_fdatawrite_range(mapping, offset, endbyte,
						   WB_SYNC_NONE);

		/*
		 * First and last FULL page! Partial pages are deliberately
		 * preserved on the expectation that it is better to preserve
		 * needed memory than to discard unneeded memory.
		 */
		start_index = (offset+(PAGE_SIZE-1)) >> PAGE_SHIFT;
		end_index = (endbyte >> PAGE_SHIFT);
		/*
		 * The page at end_index will be inclusively discarded according
		 * by invalidate_mapping_pages(), so subtracting 1 from
		 * end_index means we will skip the last page.  But if endbyte
		 * is page aligned or is at the end of file, we should not skip
		 * that page - discarding the last page is safe enough.
		 */
		if ((endbyte & ~PAGE_MASK) != ~PAGE_MASK &&
				endbyte != inode->i_size - 1) {
			/* First page is tricky as 0 - 1 = -1, but pgoff_t
			 * is unsigned, so the end_index >= start_index
			 * check below would be true and we'll discard the whole
			 * file cache which is not what was asked.
			 */
			if (end_index == 0)
				break;

			end_index--;
		}

		if (end_index >= start_index) {
			unsigned long count;

			/*
			 * It's common to FADV_DONTNEED right after
			 * the read or write that instantiates the
			 * pages, in which case there will be some
			 * sitting on the local LRU cache. Try to
			 * avoid the expensive remote drain and the
			 * second cache tree walk below by flushing
			 * them out right away.
			 */
			lru_add_drain();

			count = invalidate_mapping_pages(mapping,
						start_index, end_index);

			/*
			 * If fewer pages were invalidated than expected then
			 * it is possible that some of the pages were on
			 * a per-cpu pagevec for a remote CPU. Drain all
			 * pagevecs and try again.
			 */
			if (count < (end_index - start_index + 1)) {
				lru_add_drain_all();
				invalidate_mapping_pages(mapping, start_index,
						end_index);
			}
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}