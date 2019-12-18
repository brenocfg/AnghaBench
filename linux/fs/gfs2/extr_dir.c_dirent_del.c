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
typedef  int u16 ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct TYPE_2__ {scalar_t__ no_formal_ino; scalar_t__ no_addr; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_rec_len; TYPE_1__ de_inum; } ;
struct buffer_head {char* b_data; int b_size; } ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 scalar_t__ gfs2_dirent_sentinel (struct gfs2_dirent*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static void dirent_del(struct gfs2_inode *dip, struct buffer_head *bh,
		       struct gfs2_dirent *prev, struct gfs2_dirent *cur)
{
	u16 cur_rec_len, prev_rec_len;

	if (gfs2_dirent_sentinel(cur)) {
		gfs2_consist_inode(dip);
		return;
	}

	gfs2_trans_add_meta(dip->i_gl, bh);

	/* If there is no prev entry, this is the first entry in the block.
	   The de_rec_len is already as big as it needs to be.  Just zero
	   out the inode number and return.  */

	if (!prev) {
		cur->de_inum.no_addr = 0;
		cur->de_inum.no_formal_ino = 0;
		return;
	}

	/*  Combine this dentry with the previous one.  */

	prev_rec_len = be16_to_cpu(prev->de_rec_len);
	cur_rec_len = be16_to_cpu(cur->de_rec_len);

	if ((char *)prev + prev_rec_len != (char *)cur)
		gfs2_consist_inode(dip);
	if ((char *)cur + cur_rec_len > bh->b_data + bh->b_size)
		gfs2_consist_inode(dip);

	prev_rec_len += cur_rec_len;
	prev->de_rec_len = cpu_to_be16(prev_rec_len);
}