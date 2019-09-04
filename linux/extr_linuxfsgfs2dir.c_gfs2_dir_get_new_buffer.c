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
struct gfs2_meta_header {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_FORMAT_JD ; 
 int /*<<< orphan*/  GFS2_METATYPE_JD ; 
 int /*<<< orphan*/  gfs2_buffer_clear_tail (struct buffer_head*,int) ; 
 struct buffer_head* gfs2_meta_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_metatype_set (struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 

int gfs2_dir_get_new_buffer(struct gfs2_inode *ip, u64 block,
			    struct buffer_head **bhp)
{
	struct buffer_head *bh;

	bh = gfs2_meta_new(ip->i_gl, block);
	gfs2_trans_add_meta(ip->i_gl, bh);
	gfs2_metatype_set(bh, GFS2_METATYPE_JD, GFS2_FORMAT_JD);
	gfs2_buffer_clear_tail(bh, sizeof(struct gfs2_meta_header));
	*bhp = bh;
	return 0;
}