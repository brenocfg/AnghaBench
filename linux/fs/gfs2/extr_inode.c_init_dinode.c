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
struct TYPE_2__ {int i_mode; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_rdev; } ;
struct gfs2_inode {TYPE_1__ i_inode; int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_no_addr; } ;
struct gfs2_dinode {int /*<<< orphan*/  di_reserved; int /*<<< orphan*/  __pad4; scalar_t__ __pad3; scalar_t__ __pad2; scalar_t__ __pad1; void* di_minor; void* di_major; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
#define  S_IFDIR 129 
#define  S_IFLNK 128 
 int S_IFMT ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_buffer_clear_tail (struct buffer_head*,int) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,struct gfs2_dinode*) ; 
 int /*<<< orphan*/  gfs2_init_dir (struct buffer_head*,struct gfs2_inode*) ; 
 struct buffer_head* gfs2_meta_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

__attribute__((used)) static void init_dinode(struct gfs2_inode *dip, struct gfs2_inode *ip,
			const char *symname)
{
	struct gfs2_dinode *di;
	struct buffer_head *dibh;

	dibh = gfs2_meta_new(ip->i_gl, ip->i_no_addr);
	gfs2_trans_add_meta(ip->i_gl, dibh);
	di = (struct gfs2_dinode *)dibh->b_data;
	gfs2_dinode_out(ip, di);

	di->di_major = cpu_to_be32(MAJOR(ip->i_inode.i_rdev));
	di->di_minor = cpu_to_be32(MINOR(ip->i_inode.i_rdev));
	di->__pad1 = 0;
	di->__pad2 = 0;
	di->__pad3 = 0;
	memset(&di->__pad4, 0, sizeof(di->__pad4));
	memset(&di->di_reserved, 0, sizeof(di->di_reserved));
	gfs2_buffer_clear_tail(dibh, sizeof(struct gfs2_dinode));

	switch(ip->i_inode.i_mode & S_IFMT) {
	case S_IFDIR:
		gfs2_init_dir(dibh, dip);
		break;
	case S_IFLNK:
		memcpy(dibh->b_data + sizeof(struct gfs2_dinode), symname, ip->i_inode.i_size);
		break;
	}

	set_buffer_uptodate(dibh);
	brelse(dibh);
}