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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_inode {int i_height; int /*<<< orphan*/  i_rw_mutex; int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_dinode {int /*<<< orphan*/  di_height; void* di_blocks; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  void* __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_add_inode_blocks (int /*<<< orphan*/ *,int) ; 
 int gfs2_alloc_blocks (struct gfs2_inode*,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_buffer_clear_tail (struct buffer_head*,int) ; 
 int /*<<< orphan*/  gfs2_buffer_copy_tail (struct buffer_head*,int,struct buffer_head*,int) ; 
 int gfs2_dir_get_new_buffer (struct gfs2_inode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_get_inode_blocks (int /*<<< orphan*/ *) ; 
 int gfs2_is_dir (struct gfs2_inode*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_trans_remove_revoke (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gfs2_unstuffer_page (struct gfs2_inode*,struct buffer_head*,int /*<<< orphan*/ ,struct page*) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int gfs2_unstuff_dinode(struct gfs2_inode *ip, struct page *page)
{
	struct buffer_head *bh, *dibh;
	struct gfs2_dinode *di;
	u64 block = 0;
	int isdir = gfs2_is_dir(ip);
	int error;

	down_write(&ip->i_rw_mutex);

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		goto out;

	if (i_size_read(&ip->i_inode)) {
		/* Get a free block, fill it with the stuffed data,
		   and write it out to disk */

		unsigned int n = 1;
		error = gfs2_alloc_blocks(ip, &block, &n, 0, NULL);
		if (error)
			goto out_brelse;
		if (isdir) {
			gfs2_trans_remove_revoke(GFS2_SB(&ip->i_inode), block, 1);
			error = gfs2_dir_get_new_buffer(ip, block, &bh);
			if (error)
				goto out_brelse;
			gfs2_buffer_copy_tail(bh, sizeof(struct gfs2_meta_header),
					      dibh, sizeof(struct gfs2_dinode));
			brelse(bh);
		} else {
			error = gfs2_unstuffer_page(ip, dibh, block, page);
			if (error)
				goto out_brelse;
		}
	}

	/*  Set up the pointer to the new block  */

	gfs2_trans_add_meta(ip->i_gl, dibh);
	di = (struct gfs2_dinode *)dibh->b_data;
	gfs2_buffer_clear_tail(dibh, sizeof(struct gfs2_dinode));

	if (i_size_read(&ip->i_inode)) {
		*(__be64 *)(di + 1) = cpu_to_be64(block);
		gfs2_add_inode_blocks(&ip->i_inode, 1);
		di->di_blocks = cpu_to_be64(gfs2_get_inode_blocks(&ip->i_inode));
	}

	ip->i_height = 1;
	di->di_height = cpu_to_be16(1);

out_brelse:
	brelse(dibh);
out:
	up_write(&ip->i_rw_mutex);
	return error;
}