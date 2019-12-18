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
typedef  int u64 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_fs_info {int /*<<< orphan*/  delalloc_workers; int /*<<< orphan*/  async_delalloc_pages; } ;
struct async_cow {int /*<<< orphan*/  num_chunks; struct async_chunk* chunks; } ;
struct async_chunk {int start; int end; unsigned int write_flags; int /*<<< orphan*/  work; int /*<<< orphan*/  extents; struct page* locked_page; struct inode* inode; int /*<<< orphan*/ * pending; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  io_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NOCOMPRESS ; 
 void* DIV_ROUND_UP (int,int) ; 
 int ENOMEM ; 
 unsigned int EXTENT_DEFRAG ; 
 unsigned int EXTENT_DELALLOC ; 
 unsigned int EXTENT_DELALLOC_NEW ; 
 unsigned int EXTENT_DO_ACCOUNTING ; 
 unsigned int EXTENT_LOCKED ; 
 int /*<<< orphan*/  FORCE_COMPRESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long PAGE_CLEAR_DIRTY ; 
 unsigned long PAGE_END_WRITEBACK ; 
 unsigned long PAGE_SET_ERROR ; 
 unsigned long PAGE_SET_WRITEBACK ; 
 int PAGE_SIZE ; 
 unsigned long PAGE_UNLOCK ; 
 int SZ_512K ; 
 int /*<<< orphan*/  async_cow_free ; 
 int /*<<< orphan*/  async_cow_start ; 
 int /*<<< orphan*/  async_cow_submit ; 
 int /*<<< orphan*/  atomic_add (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  btrfs_delalloc_helper ; 
 int /*<<< orphan*/  btrfs_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunks ; 
 int /*<<< orphan*/  extent_clear_unlock_delalloc (struct inode*,int,int,struct page*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 struct async_cow* kvmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memalloc_nofs_restore (unsigned int) ; 
 unsigned int memalloc_nofs_save () ; 
 int min (int,int) ; 
 int /*<<< orphan*/  struct_size (struct async_cow*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock_extent (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int cow_file_range_async(struct inode *inode, struct page *locked_page,
				u64 start, u64 end, int *page_started,
				unsigned long *nr_written,
				unsigned int write_flags)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct async_cow *ctx;
	struct async_chunk *async_chunk;
	unsigned long nr_pages;
	u64 cur_end;
	u64 num_chunks = DIV_ROUND_UP(end - start, SZ_512K);
	int i;
	bool should_compress;
	unsigned nofs_flag;

	unlock_extent(&BTRFS_I(inode)->io_tree, start, end);

	if (BTRFS_I(inode)->flags & BTRFS_INODE_NOCOMPRESS &&
	    !btrfs_test_opt(fs_info, FORCE_COMPRESS)) {
		num_chunks = 1;
		should_compress = false;
	} else {
		should_compress = true;
	}

	nofs_flag = memalloc_nofs_save();
	ctx = kvmalloc(struct_size(ctx, chunks, num_chunks), GFP_KERNEL);
	memalloc_nofs_restore(nofs_flag);

	if (!ctx) {
		unsigned clear_bits = EXTENT_LOCKED | EXTENT_DELALLOC |
			EXTENT_DELALLOC_NEW | EXTENT_DEFRAG |
			EXTENT_DO_ACCOUNTING;
		unsigned long page_ops = PAGE_UNLOCK | PAGE_CLEAR_DIRTY |
			PAGE_SET_WRITEBACK | PAGE_END_WRITEBACK |
			PAGE_SET_ERROR;

		extent_clear_unlock_delalloc(inode, start, end, locked_page,
					     clear_bits, page_ops);
		return -ENOMEM;
	}

	async_chunk = ctx->chunks;
	atomic_set(&ctx->num_chunks, num_chunks);

	for (i = 0; i < num_chunks; i++) {
		if (should_compress)
			cur_end = min(end, start + SZ_512K - 1);
		else
			cur_end = end;

		/*
		 * igrab is called higher up in the call chain, take only the
		 * lightweight reference for the callback lifetime
		 */
		ihold(inode);
		async_chunk[i].pending = &ctx->num_chunks;
		async_chunk[i].inode = inode;
		async_chunk[i].start = start;
		async_chunk[i].end = cur_end;
		async_chunk[i].locked_page = locked_page;
		async_chunk[i].write_flags = write_flags;
		INIT_LIST_HEAD(&async_chunk[i].extents);

		btrfs_init_work(&async_chunk[i].work,
				btrfs_delalloc_helper,
				async_cow_start, async_cow_submit,
				async_cow_free);

		nr_pages = DIV_ROUND_UP(cur_end - start, PAGE_SIZE);
		atomic_add(nr_pages, &fs_info->async_delalloc_pages);

		btrfs_queue_work(fs_info->delalloc_workers, &async_chunk[i].work);

		*nr_written += nr_pages;
		start = cur_end + 1;
	}
	*page_started = 1;
	return 0;
}