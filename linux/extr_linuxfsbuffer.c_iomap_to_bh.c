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
struct iomap {scalar_t__ offset; scalar_t__ length; int type; int flags; scalar_t__ addr; int /*<<< orphan*/  bdev; } ;
struct inode {scalar_t__ i_blkbits; } ;
struct buffer_head {scalar_t__ b_blocknr; int /*<<< orphan*/  b_bdev; } ;
typedef  scalar_t__ sector_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  IOMAP_DELALLOC 131 
 int IOMAP_F_NEW ; 
#define  IOMAP_HOLE 130 
#define  IOMAP_MAPPED 129 
#define  IOMAP_UNWRITTEN 128 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  set_buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

__attribute__((used)) static void
iomap_to_bh(struct inode *inode, sector_t block, struct buffer_head *bh,
		struct iomap *iomap)
{
	loff_t offset = block << inode->i_blkbits;

	bh->b_bdev = iomap->bdev;

	/*
	 * Block points to offset in file we need to map, iomap contains
	 * the offset at which the map starts. If the map ends before the
	 * current block, then do not map the buffer and let the caller
	 * handle it.
	 */
	BUG_ON(offset >= iomap->offset + iomap->length);

	switch (iomap->type) {
	case IOMAP_HOLE:
		/*
		 * If the buffer is not up to date or beyond the current EOF,
		 * we need to mark it as new to ensure sub-block zeroing is
		 * executed if necessary.
		 */
		if (!buffer_uptodate(bh) ||
		    (offset >= i_size_read(inode)))
			set_buffer_new(bh);
		break;
	case IOMAP_DELALLOC:
		if (!buffer_uptodate(bh) ||
		    (offset >= i_size_read(inode)))
			set_buffer_new(bh);
		set_buffer_uptodate(bh);
		set_buffer_mapped(bh);
		set_buffer_delay(bh);
		break;
	case IOMAP_UNWRITTEN:
		/*
		 * For unwritten regions, we always need to ensure that regions
		 * in the block we are not writing to are zeroed. Mark the
		 * buffer as new to ensure this.
		 */
		set_buffer_new(bh);
		set_buffer_unwritten(bh);
		/* FALLTHRU */
	case IOMAP_MAPPED:
		if ((iomap->flags & IOMAP_F_NEW) ||
		    offset >= i_size_read(inode))
			set_buffer_new(bh);
		bh->b_blocknr = (iomap->addr + offset - iomap->offset) >>
				inode->i_blkbits;
		set_buffer_mapped(bh);
		break;
	}
}