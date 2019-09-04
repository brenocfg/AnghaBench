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
struct super_block {int s_blocksize_bits; } ;
struct page {int index; TYPE_1__* mapping; } ;
struct inode {struct super_block* i_sb; } ;
struct ext4_group_info {char* bb_counters; scalar_t__ bb_fragments; } ;
struct buffer_head {char* b_data; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  size_t ext4_group_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_MB_GRP_NEED_INIT (struct ext4_group_info*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct buffer_head*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_verified (struct buffer_head*) ; 
 struct ext4_group_info* ext4_get_group_info (struct super_block*,size_t) ; 
 size_t ext4_get_groups_count (struct super_block*) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,size_t) ; 
 int /*<<< orphan*/  ext4_mb_generate_buddy (struct super_block*,char*,char*,size_t) ; 
 int /*<<< orphan*/  ext4_mb_generate_from_freelist (struct super_block*,char*,size_t) ; 
 int /*<<< orphan*/  ext4_mb_generate_from_pa (struct super_block*,char*,size_t) ; 
 struct buffer_head* ext4_read_block_bitmap_nowait (struct super_block*,size_t) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,size_t) ; 
 int ext4_wait_block_bitmap (struct super_block*,size_t,struct buffer_head*) ; 
 int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct buffer_head**) ; 
 struct buffer_head** kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_debug (int,char*,size_t,...) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 char* page_address (struct page*) ; 
 int /*<<< orphan*/  trace_ext4_mb_bitmap_load (struct super_block*,size_t) ; 
 int /*<<< orphan*/  trace_ext4_mb_buddy_bitmap_load (struct super_block*,size_t) ; 

__attribute__((used)) static int ext4_mb_init_cache(struct page *page, char *incore, gfp_t gfp)
{
	ext4_group_t ngroups;
	int blocksize;
	int blocks_per_page;
	int groups_per_page;
	int err = 0;
	int i;
	ext4_group_t first_group, group;
	int first_block;
	struct super_block *sb;
	struct buffer_head *bhs;
	struct buffer_head **bh = NULL;
	struct inode *inode;
	char *data;
	char *bitmap;
	struct ext4_group_info *grinfo;

	mb_debug(1, "init page %lu\n", page->index);

	inode = page->mapping->host;
	sb = inode->i_sb;
	ngroups = ext4_get_groups_count(sb);
	blocksize = i_blocksize(inode);
	blocks_per_page = PAGE_SIZE / blocksize;

	groups_per_page = blocks_per_page >> 1;
	if (groups_per_page == 0)
		groups_per_page = 1;

	/* allocate buffer_heads to read bitmaps */
	if (groups_per_page > 1) {
		i = sizeof(struct buffer_head *) * groups_per_page;
		bh = kzalloc(i, gfp);
		if (bh == NULL) {
			err = -ENOMEM;
			goto out;
		}
	} else
		bh = &bhs;

	first_group = page->index * blocks_per_page / 2;

	/* read all groups the page covers into the cache */
	for (i = 0, group = first_group; i < groups_per_page; i++, group++) {
		if (group >= ngroups)
			break;

		grinfo = ext4_get_group_info(sb, group);
		/*
		 * If page is uptodate then we came here after online resize
		 * which added some new uninitialized group info structs, so
		 * we must skip all initialized uptodate buddies on the page,
		 * which may be currently in use by an allocating task.
		 */
		if (PageUptodate(page) && !EXT4_MB_GRP_NEED_INIT(grinfo)) {
			bh[i] = NULL;
			continue;
		}
		bh[i] = ext4_read_block_bitmap_nowait(sb, group);
		if (IS_ERR(bh[i])) {
			err = PTR_ERR(bh[i]);
			bh[i] = NULL;
			goto out;
		}
		mb_debug(1, "read bitmap for group %u\n", group);
	}

	/* wait for I/O completion */
	for (i = 0, group = first_group; i < groups_per_page; i++, group++) {
		int err2;

		if (!bh[i])
			continue;
		err2 = ext4_wait_block_bitmap(sb, group, bh[i]);
		if (!err)
			err = err2;
	}

	first_block = page->index * blocks_per_page;
	for (i = 0; i < blocks_per_page; i++) {
		group = (first_block + i) >> 1;
		if (group >= ngroups)
			break;

		if (!bh[group - first_group])
			/* skip initialized uptodate buddy */
			continue;

		if (!buffer_verified(bh[group - first_group]))
			/* Skip faulty bitmaps */
			continue;
		err = 0;

		/*
		 * data carry information regarding this
		 * particular group in the format specified
		 * above
		 *
		 */
		data = page_address(page) + (i * blocksize);
		bitmap = bh[group - first_group]->b_data;

		/*
		 * We place the buddy block and bitmap block
		 * close together
		 */
		if ((first_block + i) & 1) {
			/* this is block of buddy */
			BUG_ON(incore == NULL);
			mb_debug(1, "put buddy for group %u in page %lu/%x\n",
				group, page->index, i * blocksize);
			trace_ext4_mb_buddy_bitmap_load(sb, group);
			grinfo = ext4_get_group_info(sb, group);
			grinfo->bb_fragments = 0;
			memset(grinfo->bb_counters, 0,
			       sizeof(*grinfo->bb_counters) *
				(sb->s_blocksize_bits+2));
			/*
			 * incore got set to the group block bitmap below
			 */
			ext4_lock_group(sb, group);
			/* init the buddy */
			memset(data, 0xff, blocksize);
			ext4_mb_generate_buddy(sb, data, incore, group);
			ext4_unlock_group(sb, group);
			incore = NULL;
		} else {
			/* this is block of bitmap */
			BUG_ON(incore != NULL);
			mb_debug(1, "put bitmap for group %u in page %lu/%x\n",
				group, page->index, i * blocksize);
			trace_ext4_mb_bitmap_load(sb, group);

			/* see comments in ext4_mb_put_pa() */
			ext4_lock_group(sb, group);
			memcpy(data, bitmap, blocksize);

			/* mark all preallocated blks used in in-core bitmap */
			ext4_mb_generate_from_pa(sb, data, group);
			ext4_mb_generate_from_freelist(sb, data, group);
			ext4_unlock_group(sb, group);

			/* set incore so that the buddy information can be
			 * generated using this
			 */
			incore = data;
		}
	}
	SetPageUptodate(page);

out:
	if (bh) {
		for (i = 0; i < groups_per_page; i++)
			brelse(bh[i]);
		if (bh != &bhs)
			kfree(bh);
	}
	return err;
}