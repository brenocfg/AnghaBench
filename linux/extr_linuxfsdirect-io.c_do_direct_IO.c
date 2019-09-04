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
struct page {int dummy; } ;
struct dio_submit {unsigned int blkbits; unsigned int const blkfactor; unsigned long block_in_file; unsigned long final_block_in_request; int head; size_t from; int tail; size_t to; unsigned int blocks_available; int next_block_for_io; int /*<<< orphan*/  boundary; int /*<<< orphan*/  start_zero_done; } ;
struct dio {scalar_t__ op; int result; int /*<<< orphan*/  inode; } ;
struct buffer_head {unsigned int const b_size; int b_blocknr; int /*<<< orphan*/  b_bdev; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOTBLK ; 
 scalar_t__ IS_ERR (struct page*) ; 
 size_t PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ REQ_OP_WRITE ; 
 int /*<<< orphan*/  buffer_boundary (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  clean_bdev_aliases (int /*<<< orphan*/ ,int,unsigned int const) ; 
 struct page* dio_get_page (struct dio*,struct dio_submit*) ; 
 int /*<<< orphan*/  dio_zero_block (struct dio*,struct dio_submit*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int get_more_blocks (struct dio*,struct dio_submit*,struct buffer_head*) ; 
 int /*<<< orphan*/  i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int submit_page_section (struct dio*,struct dio_submit*,struct page*,size_t,unsigned int,unsigned long,struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zero_user (struct page*,size_t,int) ; 

__attribute__((used)) static int do_direct_IO(struct dio *dio, struct dio_submit *sdio,
			struct buffer_head *map_bh)
{
	const unsigned blkbits = sdio->blkbits;
	const unsigned i_blkbits = blkbits + sdio->blkfactor;
	int ret = 0;

	while (sdio->block_in_file < sdio->final_block_in_request) {
		struct page *page;
		size_t from, to;

		page = dio_get_page(dio, sdio);
		if (IS_ERR(page)) {
			ret = PTR_ERR(page);
			goto out;
		}
		from = sdio->head ? 0 : sdio->from;
		to = (sdio->head == sdio->tail - 1) ? sdio->to : PAGE_SIZE;
		sdio->head++;

		while (from < to) {
			unsigned this_chunk_bytes;	/* # of bytes mapped */
			unsigned this_chunk_blocks;	/* # of blocks */
			unsigned u;

			if (sdio->blocks_available == 0) {
				/*
				 * Need to go and map some more disk
				 */
				unsigned long blkmask;
				unsigned long dio_remainder;

				ret = get_more_blocks(dio, sdio, map_bh);
				if (ret) {
					put_page(page);
					goto out;
				}
				if (!buffer_mapped(map_bh))
					goto do_holes;

				sdio->blocks_available =
						map_bh->b_size >> blkbits;
				sdio->next_block_for_io =
					map_bh->b_blocknr << sdio->blkfactor;
				if (buffer_new(map_bh)) {
					clean_bdev_aliases(
						map_bh->b_bdev,
						map_bh->b_blocknr,
						map_bh->b_size >> i_blkbits);
				}

				if (!sdio->blkfactor)
					goto do_holes;

				blkmask = (1 << sdio->blkfactor) - 1;
				dio_remainder = (sdio->block_in_file & blkmask);

				/*
				 * If we are at the start of IO and that IO
				 * starts partway into a fs-block,
				 * dio_remainder will be non-zero.  If the IO
				 * is a read then we can simply advance the IO
				 * cursor to the first block which is to be
				 * read.  But if the IO is a write and the
				 * block was newly allocated we cannot do that;
				 * the start of the fs block must be zeroed out
				 * on-disk
				 */
				if (!buffer_new(map_bh))
					sdio->next_block_for_io += dio_remainder;
				sdio->blocks_available -= dio_remainder;
			}
do_holes:
			/* Handle holes */
			if (!buffer_mapped(map_bh)) {
				loff_t i_size_aligned;

				/* AKPM: eargh, -ENOTBLK is a hack */
				if (dio->op == REQ_OP_WRITE) {
					put_page(page);
					return -ENOTBLK;
				}

				/*
				 * Be sure to account for a partial block as the
				 * last block in the file
				 */
				i_size_aligned = ALIGN(i_size_read(dio->inode),
							1 << blkbits);
				if (sdio->block_in_file >=
						i_size_aligned >> blkbits) {
					/* We hit eof */
					put_page(page);
					goto out;
				}
				zero_user(page, from, 1 << blkbits);
				sdio->block_in_file++;
				from += 1 << blkbits;
				dio->result += 1 << blkbits;
				goto next_block;
			}

			/*
			 * If we're performing IO which has an alignment which
			 * is finer than the underlying fs, go check to see if
			 * we must zero out the start of this block.
			 */
			if (unlikely(sdio->blkfactor && !sdio->start_zero_done))
				dio_zero_block(dio, sdio, 0, map_bh);

			/*
			 * Work out, in this_chunk_blocks, how much disk we
			 * can add to this page
			 */
			this_chunk_blocks = sdio->blocks_available;
			u = (to - from) >> blkbits;
			if (this_chunk_blocks > u)
				this_chunk_blocks = u;
			u = sdio->final_block_in_request - sdio->block_in_file;
			if (this_chunk_blocks > u)
				this_chunk_blocks = u;
			this_chunk_bytes = this_chunk_blocks << blkbits;
			BUG_ON(this_chunk_bytes == 0);

			if (this_chunk_blocks == sdio->blocks_available)
				sdio->boundary = buffer_boundary(map_bh);
			ret = submit_page_section(dio, sdio, page,
						  from,
						  this_chunk_bytes,
						  sdio->next_block_for_io,
						  map_bh);
			if (ret) {
				put_page(page);
				goto out;
			}
			sdio->next_block_for_io += this_chunk_blocks;

			sdio->block_in_file += this_chunk_blocks;
			from += this_chunk_bytes;
			dio->result += this_chunk_bytes;
			sdio->blocks_available -= this_chunk_blocks;
next_block:
			BUG_ON(sdio->block_in_file > sdio->final_block_in_request);
			if (sdio->block_in_file == sdio->final_block_in_request)
				break;
		}

		/* Drop the ref which was taken in get_user_pages() */
		put_page(page);
	}
out:
	return ret;
}