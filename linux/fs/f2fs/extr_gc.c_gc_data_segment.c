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
struct super_block {int dummy; } ;
struct page {int /*<<< orphan*/  i_mode; } ;
struct node_info {int /*<<< orphan*/  ino; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct gc_inode_list {int dummy; } ;
struct f2fs_summary {int /*<<< orphan*/  ofs_in_node; int /*<<< orphan*/  nid; } ;
struct f2fs_sb_info {int blocks_per_seg; int /*<<< orphan*/  skipped_gc_rwsem; struct super_block* sb; } ;
struct f2fs_inode_info {int /*<<< orphan*/ * i_gc_rwsem; } ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 int BG_GC ; 
 struct f2fs_inode_info* F2FS_I (struct page*) ; 
 int FG_GC ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  META_NAT ; 
 int /*<<< orphan*/  NAT_BLOCK_OFFSET (int /*<<< orphan*/ ) ; 
 size_t READ ; 
 int /*<<< orphan*/  REQ_RAHEAD ; 
 scalar_t__ START_BLOCK (struct f2fs_sb_info*,unsigned int) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 size_t WRITE ; 
 int /*<<< orphan*/  add_gc_inode (struct gc_inode_list*,struct page*) ; 
 scalar_t__ check_valid_map (struct f2fs_sb_info*,unsigned int,int) ; 
 int /*<<< orphan*/  down_write_trylock (int /*<<< orphan*/ *) ; 
 struct page* f2fs_get_read_data_page (struct page*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct page* f2fs_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_post_read_required (struct page*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_ra_meta_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_ra_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_start_bidx_of_node (unsigned int,struct page*) ; 
 struct page* find_gc_inode (struct gc_inode_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_not_enough_free_secs (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_dio_wait (struct page*) ; 
 int /*<<< orphan*/  iput (struct page*) ; 
 int /*<<< orphan*/  is_alive (struct f2fs_sb_info*,struct f2fs_summary*,struct node_info*,scalar_t__,unsigned int*) ; 
 scalar_t__ is_bad_inode (struct page*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int move_data_block (struct page*,scalar_t__,int,unsigned int,int) ; 
 int move_data_page (struct page*,scalar_t__,int,unsigned int,int) ; 
 int ra_data_block (struct page*,scalar_t__) ; 
 int /*<<< orphan*/  stat_inc_data_blk_count (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gc_data_segment(struct f2fs_sb_info *sbi, struct f2fs_summary *sum,
		struct gc_inode_list *gc_list, unsigned int segno, int gc_type)
{
	struct super_block *sb = sbi->sb;
	struct f2fs_summary *entry;
	block_t start_addr;
	int off;
	int phase = 0;
	int submitted = 0;

	start_addr = START_BLOCK(sbi, segno);

next_step:
	entry = sum;

	for (off = 0; off < sbi->blocks_per_seg; off++, entry++) {
		struct page *data_page;
		struct inode *inode;
		struct node_info dni; /* dnode info for the data */
		unsigned int ofs_in_node, nofs;
		block_t start_bidx;
		nid_t nid = le32_to_cpu(entry->nid);

		/* stop BG_GC if there is not enough free sections. */
		if (gc_type == BG_GC && has_not_enough_free_secs(sbi, 0, 0))
			return submitted;

		if (check_valid_map(sbi, segno, off) == 0)
			continue;

		if (phase == 0) {
			f2fs_ra_meta_pages(sbi, NAT_BLOCK_OFFSET(nid), 1,
							META_NAT, true);
			continue;
		}

		if (phase == 1) {
			f2fs_ra_node_page(sbi, nid);
			continue;
		}

		/* Get an inode by ino with checking validity */
		if (!is_alive(sbi, entry, &dni, start_addr + off, &nofs))
			continue;

		if (phase == 2) {
			f2fs_ra_node_page(sbi, dni.ino);
			continue;
		}

		ofs_in_node = le16_to_cpu(entry->ofs_in_node);

		if (phase == 3) {
			inode = f2fs_iget(sb, dni.ino);
			if (IS_ERR(inode) || is_bad_inode(inode))
				continue;

			if (!down_write_trylock(
				&F2FS_I(inode)->i_gc_rwsem[WRITE])) {
				iput(inode);
				sbi->skipped_gc_rwsem++;
				continue;
			}

			start_bidx = f2fs_start_bidx_of_node(nofs, inode) +
								ofs_in_node;

			if (f2fs_post_read_required(inode)) {
				int err = ra_data_block(inode, start_bidx);

				up_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
				if (err) {
					iput(inode);
					continue;
				}
				add_gc_inode(gc_list, inode);
				continue;
			}

			data_page = f2fs_get_read_data_page(inode,
						start_bidx, REQ_RAHEAD, true);
			up_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
			if (IS_ERR(data_page)) {
				iput(inode);
				continue;
			}

			f2fs_put_page(data_page, 0);
			add_gc_inode(gc_list, inode);
			continue;
		}

		/* phase 4 */
		inode = find_gc_inode(gc_list, dni.ino);
		if (inode) {
			struct f2fs_inode_info *fi = F2FS_I(inode);
			bool locked = false;
			int err;

			if (S_ISREG(inode->i_mode)) {
				if (!down_write_trylock(&fi->i_gc_rwsem[READ]))
					continue;
				if (!down_write_trylock(
						&fi->i_gc_rwsem[WRITE])) {
					sbi->skipped_gc_rwsem++;
					up_write(&fi->i_gc_rwsem[READ]);
					continue;
				}
				locked = true;

				/* wait for all inflight aio data */
				inode_dio_wait(inode);
			}

			start_bidx = f2fs_start_bidx_of_node(nofs, inode)
								+ ofs_in_node;
			if (f2fs_post_read_required(inode))
				err = move_data_block(inode, start_bidx,
							gc_type, segno, off);
			else
				err = move_data_page(inode, start_bidx, gc_type,
								segno, off);

			if (!err && (gc_type == FG_GC ||
					f2fs_post_read_required(inode)))
				submitted++;

			if (locked) {
				up_write(&fi->i_gc_rwsem[WRITE]);
				up_write(&fi->i_gc_rwsem[READ]);
			}

			stat_inc_data_blk_count(sbi, 1, gc_type);
		}
	}

	if (++phase < 5)
		goto next_step;

	return submitted;
}