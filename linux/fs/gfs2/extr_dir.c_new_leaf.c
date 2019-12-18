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
typedef  int /*<<< orphan*/  u16 ;
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int dummy; } ;
struct gfs2_leaf {int /*<<< orphan*/  lf_reserved2; void* lf_sec; void* lf_nsec; void* lf_dist; void* lf_inode; scalar_t__ lf_next; void* lf_dirent_format; scalar_t__ lf_entries; int /*<<< orphan*/  lf_depth; } ;
struct gfs2_inode {int /*<<< orphan*/  i_no_addr; int /*<<< orphan*/  i_gl; } ;
struct gfs2_dirent {int dummy; } ;
struct buffer_head {scalar_t__ b_size; scalar_t__ b_data; } ;

/* Variables and functions */
 int GFS2_FORMAT_DE ; 
 int /*<<< orphan*/  GFS2_FORMAT_LF ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  GFS2_METATYPE_LF ; 
 int /*<<< orphan*/  GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct timespec64 current_time (struct inode*) ; 
 int /*<<< orphan*/  empty_name ; 
 int gfs2_alloc_blocks (struct gfs2_inode*,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct buffer_head* gfs2_meta_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_metatype_set (struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_qstr2dirent (int /*<<< orphan*/ *,scalar_t__,struct gfs2_dirent*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_trans_remove_revoke (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct gfs2_leaf *new_leaf(struct inode *inode, struct buffer_head **pbh, u16 depth)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	unsigned int n = 1;
	u64 bn;
	int error;
	struct buffer_head *bh;
	struct gfs2_leaf *leaf;
	struct gfs2_dirent *dent;
	struct timespec64 tv = current_time(inode);

	error = gfs2_alloc_blocks(ip, &bn, &n, 0, NULL);
	if (error)
		return NULL;
	bh = gfs2_meta_new(ip->i_gl, bn);
	if (!bh)
		return NULL;

	gfs2_trans_remove_revoke(GFS2_SB(inode), bn, 1);
	gfs2_trans_add_meta(ip->i_gl, bh);
	gfs2_metatype_set(bh, GFS2_METATYPE_LF, GFS2_FORMAT_LF);
	leaf = (struct gfs2_leaf *)bh->b_data;
	leaf->lf_depth = cpu_to_be16(depth);
	leaf->lf_entries = 0;
	leaf->lf_dirent_format = cpu_to_be32(GFS2_FORMAT_DE);
	leaf->lf_next = 0;
	leaf->lf_inode = cpu_to_be64(ip->i_no_addr);
	leaf->lf_dist = cpu_to_be32(1);
	leaf->lf_nsec = cpu_to_be32(tv.tv_nsec);
	leaf->lf_sec = cpu_to_be64(tv.tv_sec);
	memset(leaf->lf_reserved2, 0, sizeof(leaf->lf_reserved2));
	dent = (struct gfs2_dirent *)(leaf+1);
	gfs2_qstr2dirent(&empty_name, bh->b_size - sizeof(struct gfs2_leaf), dent);
	*pbh = bh;
	return leaf;
}