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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct cmp_pages {void* dst_pages; void* src_pages; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NODATASUM ; 
 scalar_t__ BTRFS_MAX_DEDUPE_LEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int PAGE_ALIGN (scalar_t__) ; 
 int PAGE_SHIFT ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  btrfs_double_inode_lock (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_double_inode_unlock (struct inode*,struct inode*) ; 
 int btrfs_extent_same_range (struct inode*,scalar_t__,scalar_t__,struct inode*,scalar_t__,struct cmp_pages*) ; 
 scalar_t__ div_u64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvmalloc_array (int,int,int) ; 
 int /*<<< orphan*/  swap (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int btrfs_extent_same(struct inode *src, u64 loff, u64 olen,
			     struct inode *dst, u64 dst_loff)
{
	int ret;
	struct cmp_pages cmp;
	int num_pages = PAGE_ALIGN(BTRFS_MAX_DEDUPE_LEN) >> PAGE_SHIFT;
	bool same_inode = (src == dst);
	u64 i, tail_len, chunk_count;

	if (olen == 0)
		return 0;

	if (same_inode)
		inode_lock(src);
	else
		btrfs_double_inode_lock(src, dst);

	/* don't make the dst file partly checksummed */
	if ((BTRFS_I(src)->flags & BTRFS_INODE_NODATASUM) !=
	    (BTRFS_I(dst)->flags & BTRFS_INODE_NODATASUM)) {
		ret = -EINVAL;
		goto out_unlock;
	}

	tail_len = olen % BTRFS_MAX_DEDUPE_LEN;
	chunk_count = div_u64(olen, BTRFS_MAX_DEDUPE_LEN);
	if (chunk_count == 0)
		num_pages = PAGE_ALIGN(tail_len) >> PAGE_SHIFT;

	/*
	 * If deduping ranges in the same inode, locking rules make it
	 * mandatory to always lock pages in ascending order to avoid deadlocks
	 * with concurrent tasks (such as starting writeback/delalloc).
	 */
	if (same_inode && dst_loff < loff)
		swap(loff, dst_loff);

	/*
	 * We must gather up all the pages before we initiate our extent
	 * locking. We use an array for the page pointers. Size of the array is
	 * bounded by len, which is in turn bounded by BTRFS_MAX_DEDUPE_LEN.
	 */
	cmp.src_pages = kvmalloc_array(num_pages, sizeof(struct page *),
				       GFP_KERNEL | __GFP_ZERO);
	cmp.dst_pages = kvmalloc_array(num_pages, sizeof(struct page *),
				       GFP_KERNEL | __GFP_ZERO);
	if (!cmp.src_pages || !cmp.dst_pages) {
		ret = -ENOMEM;
		goto out_free;
	}

	for (i = 0; i < chunk_count; i++) {
		ret = btrfs_extent_same_range(src, loff, BTRFS_MAX_DEDUPE_LEN,
					      dst, dst_loff, &cmp);
		if (ret)
			goto out_free;

		loff += BTRFS_MAX_DEDUPE_LEN;
		dst_loff += BTRFS_MAX_DEDUPE_LEN;
	}

	if (tail_len > 0)
		ret = btrfs_extent_same_range(src, loff, tail_len, dst,
					      dst_loff, &cmp);

out_free:
	kvfree(cmp.src_pages);
	kvfree(cmp.dst_pages);

out_unlock:
	if (same_inode)
		inode_unlock(src);
	else
		btrfs_double_inode_unlock(src, dst);

	return ret;
}