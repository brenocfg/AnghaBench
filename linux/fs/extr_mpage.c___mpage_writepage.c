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
struct writeback_control {int dummy; } ;
struct page {unsigned long index; struct address_space* mapping; } ;
struct mpage_data {scalar_t__ last_block_in_bio; struct bio* bio; scalar_t__ use_writepage; scalar_t__ (* get_block ) (struct inode*,scalar_t__,struct buffer_head*,int) ;} ;
struct inode {unsigned int i_blkbits; int /*<<< orphan*/  i_write_hint; } ;
struct buffer_head {scalar_t__ b_blocknr; int b_size; struct block_device* b_bdev; scalar_t__ b_state; struct page* b_page; struct buffer_head* b_this_page; } ;
struct block_device {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_write_hint; } ;
struct address_space {TYPE_1__* a_ops; struct inode* host; } ;
typedef  scalar_t__ sector_t ;
typedef  int loff_t ;
struct TYPE_2__ {int (* writepage ) (struct page*,struct writeback_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int GFP_NOFS ; 
 int MAX_BUF_PER_PAGE ; 
 unsigned int const PAGE_SHIFT ; 
 unsigned int const PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int PageWriteback (struct page*) ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int __GFP_HIGH ; 
 int /*<<< orphan*/  bdev_write_page (struct block_device*,scalar_t__,struct page*,struct writeback_control*) ; 
 int bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 int buffer_boundary (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clean_bdev_bh_alias (struct buffer_head*) ; 
 int /*<<< orphan*/  clean_buffers (struct page*,unsigned int) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mapping_set_error (struct address_space*,int) ; 
 struct bio* mpage_alloc (struct block_device*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct bio* mpage_bio_submit (int /*<<< orphan*/ ,int,struct bio*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 scalar_t__ stub1 (struct inode*,scalar_t__,struct buffer_head*,int) ; 
 int stub2 (struct page*,struct writeback_control*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wbc_account_cgroup_owner (struct writeback_control*,struct page*,unsigned int const) ; 
 int /*<<< orphan*/  wbc_init_bio (struct writeback_control*,struct bio*) ; 
 int wbc_to_write_flags (struct writeback_control*) ; 
 int /*<<< orphan*/  write_boundary_block (struct block_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,unsigned int const) ; 

__attribute__((used)) static int __mpage_writepage(struct page *page, struct writeback_control *wbc,
		      void *data)
{
	struct mpage_data *mpd = data;
	struct bio *bio = mpd->bio;
	struct address_space *mapping = page->mapping;
	struct inode *inode = page->mapping->host;
	const unsigned blkbits = inode->i_blkbits;
	unsigned long end_index;
	const unsigned blocks_per_page = PAGE_SIZE >> blkbits;
	sector_t last_block;
	sector_t block_in_file;
	sector_t blocks[MAX_BUF_PER_PAGE];
	unsigned page_block;
	unsigned first_unmapped = blocks_per_page;
	struct block_device *bdev = NULL;
	int boundary = 0;
	sector_t boundary_block = 0;
	struct block_device *boundary_bdev = NULL;
	int length;
	struct buffer_head map_bh;
	loff_t i_size = i_size_read(inode);
	int ret = 0;
	int op_flags = wbc_to_write_flags(wbc);

	if (page_has_buffers(page)) {
		struct buffer_head *head = page_buffers(page);
		struct buffer_head *bh = head;

		/* If they're all mapped and dirty, do it */
		page_block = 0;
		do {
			BUG_ON(buffer_locked(bh));
			if (!buffer_mapped(bh)) {
				/*
				 * unmapped dirty buffers are created by
				 * __set_page_dirty_buffers -> mmapped data
				 */
				if (buffer_dirty(bh))
					goto confused;
				if (first_unmapped == blocks_per_page)
					first_unmapped = page_block;
				continue;
			}

			if (first_unmapped != blocks_per_page)
				goto confused;	/* hole -> non-hole */

			if (!buffer_dirty(bh) || !buffer_uptodate(bh))
				goto confused;
			if (page_block) {
				if (bh->b_blocknr != blocks[page_block-1] + 1)
					goto confused;
			}
			blocks[page_block++] = bh->b_blocknr;
			boundary = buffer_boundary(bh);
			if (boundary) {
				boundary_block = bh->b_blocknr;
				boundary_bdev = bh->b_bdev;
			}
			bdev = bh->b_bdev;
		} while ((bh = bh->b_this_page) != head);

		if (first_unmapped)
			goto page_is_mapped;

		/*
		 * Page has buffers, but they are all unmapped. The page was
		 * created by pagein or read over a hole which was handled by
		 * block_read_full_page().  If this address_space is also
		 * using mpage_readpages then this can rarely happen.
		 */
		goto confused;
	}

	/*
	 * The page has no buffers: map it to disk
	 */
	BUG_ON(!PageUptodate(page));
	block_in_file = (sector_t)page->index << (PAGE_SHIFT - blkbits);
	last_block = (i_size - 1) >> blkbits;
	map_bh.b_page = page;
	for (page_block = 0; page_block < blocks_per_page; ) {

		map_bh.b_state = 0;
		map_bh.b_size = 1 << blkbits;
		if (mpd->get_block(inode, block_in_file, &map_bh, 1))
			goto confused;
		if (buffer_new(&map_bh))
			clean_bdev_bh_alias(&map_bh);
		if (buffer_boundary(&map_bh)) {
			boundary_block = map_bh.b_blocknr;
			boundary_bdev = map_bh.b_bdev;
		}
		if (page_block) {
			if (map_bh.b_blocknr != blocks[page_block-1] + 1)
				goto confused;
		}
		blocks[page_block++] = map_bh.b_blocknr;
		boundary = buffer_boundary(&map_bh);
		bdev = map_bh.b_bdev;
		if (block_in_file == last_block)
			break;
		block_in_file++;
	}
	BUG_ON(page_block == 0);

	first_unmapped = page_block;

page_is_mapped:
	end_index = i_size >> PAGE_SHIFT;
	if (page->index >= end_index) {
		/*
		 * The page straddles i_size.  It must be zeroed out on each
		 * and every writepage invocation because it may be mmapped.
		 * "A file is mapped in multiples of the page size.  For a file
		 * that is not a multiple of the page size, the remaining memory
		 * is zeroed when mapped, and writes to that region are not
		 * written out to the file."
		 */
		unsigned offset = i_size & (PAGE_SIZE - 1);

		if (page->index > end_index || !offset)
			goto confused;
		zero_user_segment(page, offset, PAGE_SIZE);
	}

	/*
	 * This page will go to BIO.  Do we need to send this BIO off first?
	 */
	if (bio && mpd->last_block_in_bio != blocks[0] - 1)
		bio = mpage_bio_submit(REQ_OP_WRITE, op_flags, bio);

alloc_new:
	if (bio == NULL) {
		if (first_unmapped == blocks_per_page) {
			if (!bdev_write_page(bdev, blocks[0] << (blkbits - 9),
								page, wbc))
				goto out;
		}
		bio = mpage_alloc(bdev, blocks[0] << (blkbits - 9),
				BIO_MAX_PAGES, GFP_NOFS|__GFP_HIGH);
		if (bio == NULL)
			goto confused;

		wbc_init_bio(wbc, bio);
		bio->bi_write_hint = inode->i_write_hint;
	}

	/*
	 * Must try to add the page before marking the buffer clean or
	 * the confused fail path above (OOM) will be very confused when
	 * it finds all bh marked clean (i.e. it will not write anything)
	 */
	wbc_account_cgroup_owner(wbc, page, PAGE_SIZE);
	length = first_unmapped << blkbits;
	if (bio_add_page(bio, page, length, 0) < length) {
		bio = mpage_bio_submit(REQ_OP_WRITE, op_flags, bio);
		goto alloc_new;
	}

	clean_buffers(page, first_unmapped);

	BUG_ON(PageWriteback(page));
	set_page_writeback(page);
	unlock_page(page);
	if (boundary || (first_unmapped != blocks_per_page)) {
		bio = mpage_bio_submit(REQ_OP_WRITE, op_flags, bio);
		if (boundary_block) {
			write_boundary_block(boundary_bdev,
					boundary_block, 1 << blkbits);
		}
	} else {
		mpd->last_block_in_bio = blocks[blocks_per_page - 1];
	}
	goto out;

confused:
	if (bio)
		bio = mpage_bio_submit(REQ_OP_WRITE, op_flags, bio);

	if (mpd->use_writepage) {
		ret = mapping->a_ops->writepage(page, wbc);
	} else {
		ret = -EAGAIN;
		goto out;
	}
	/*
	 * The caller has a ref on the inode, so *mapping is stable
	 */
	mapping_set_error(mapping, ret);
out:
	mpd->bio = bio;
	return ret;
}