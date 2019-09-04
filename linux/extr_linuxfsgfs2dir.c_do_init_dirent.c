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
struct qstr {unsigned int len; } ;
struct inode {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_rec_len; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  gfs2_qstr2dirent (struct qstr const*,unsigned int,struct gfs2_dirent*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static struct gfs2_dirent *do_init_dirent(struct inode *inode,
					  struct gfs2_dirent *dent,
					  const struct qstr *name,
					  struct buffer_head *bh,
					  unsigned offset)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_dirent *ndent;
	unsigned totlen;

	totlen = be16_to_cpu(dent->de_rec_len);
	BUG_ON(offset + name->len > totlen);
	gfs2_trans_add_meta(ip->i_gl, bh);
	ndent = (struct gfs2_dirent *)((char *)dent + offset);
	dent->de_rec_len = cpu_to_be16(offset);
	gfs2_qstr2dirent(name, totlen - offset, ndent);
	return ndent;
}