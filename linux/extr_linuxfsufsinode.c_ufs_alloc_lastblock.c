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
struct ufs_sb_private_info {int s_fsize; int s_fshift; int s_fpb; } ;
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct page {int dummy; } ;
struct inode {int i_blkbits; struct address_space* i_mapping; struct super_block* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_data; scalar_t__ b_blocknr; struct buffer_head* b_this_page; } ;
struct address_space {int dummy; } ;
typedef  int sector_t ;
typedef  int loff_t ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_SHIFT ; 
 int UFS_IND_FRAGMENT ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  clean_bdev_bh_alias (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 struct buffer_head* sb_getblk (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 int ufs_fragnum (int) ; 
 struct page* ufs_get_locked_page (struct address_space*,int) ; 
 int ufs_getfrag_block (struct inode*,int,struct buffer_head*,int) ; 
 int /*<<< orphan*/  ufs_put_locked_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int ufs_alloc_lastblock(struct inode *inode, loff_t size)
{
	int err = 0;
	struct super_block *sb = inode->i_sb;
	struct address_space *mapping = inode->i_mapping;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	unsigned i, end;
	sector_t lastfrag;
	struct page *lastpage;
	struct buffer_head *bh;
	u64 phys64;

	lastfrag = (size + uspi->s_fsize - 1) >> uspi->s_fshift;

	if (!lastfrag)
		goto out;

	lastfrag--;

	lastpage = ufs_get_locked_page(mapping, lastfrag >>
				       (PAGE_SHIFT - inode->i_blkbits));
       if (IS_ERR(lastpage)) {
               err = -EIO;
               goto out;
       }

       end = lastfrag & ((1 << (PAGE_SHIFT - inode->i_blkbits)) - 1);
       bh = page_buffers(lastpage);
       for (i = 0; i < end; ++i)
               bh = bh->b_this_page;


       err = ufs_getfrag_block(inode, lastfrag, bh, 1);

       if (unlikely(err))
	       goto out_unlock;

       if (buffer_new(bh)) {
	       clear_buffer_new(bh);
	       clean_bdev_bh_alias(bh);
	       /*
		* we do not zeroize fragment, because of
		* if it maped to hole, it already contains zeroes
		*/
	       set_buffer_uptodate(bh);
	       mark_buffer_dirty(bh);
	       set_page_dirty(lastpage);
       }

       if (lastfrag >= UFS_IND_FRAGMENT) {
	       end = uspi->s_fpb - ufs_fragnum(lastfrag) - 1;
	       phys64 = bh->b_blocknr + 1;
	       for (i = 0; i < end; ++i) {
		       bh = sb_getblk(sb, i + phys64);
		       lock_buffer(bh);
		       memset(bh->b_data, 0, sb->s_blocksize);
		       set_buffer_uptodate(bh);
		       mark_buffer_dirty(bh);
		       unlock_buffer(bh);
		       sync_dirty_buffer(bh);
		       brelse(bh);
	       }
       }
out_unlock:
       ufs_put_locked_page(lastpage);
out:
       return err;
}