#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_no_formal_ino; int /*<<< orphan*/  i_no_addr; } ;
struct gfs2_holder {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  actor; } ;
struct TYPE_3__ {int /*<<< orphan*/  no_formal_ino; int /*<<< orphan*/  no_addr; } ;
struct get_name_filldir {char* name; TYPE_2__ ctx; TYPE_1__ inum; } ;
struct file_ra_state {int /*<<< orphan*/  start; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  get_name_filldir ; 
 int gfs2_dir_read (struct inode*,TYPE_2__*,struct file_ra_state*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 

__attribute__((used)) static int gfs2_get_name(struct dentry *parent, char *name,
			 struct dentry *child)
{
	struct inode *dir = d_inode(parent);
	struct inode *inode = d_inode(child);
	struct gfs2_inode *dip, *ip;
	struct get_name_filldir gnfd = {
		.ctx.actor = get_name_filldir,
		.name = name
	};
	struct gfs2_holder gh;
	int error;
	struct file_ra_state f_ra = { .start = 0 };

	if (!dir)
		return -EINVAL;

	if (!S_ISDIR(dir->i_mode) || !inode)
		return -EINVAL;

	dip = GFS2_I(dir);
	ip = GFS2_I(inode);

	*name = 0;
	gnfd.inum.no_addr = ip->i_no_addr;
	gnfd.inum.no_formal_ino = ip->i_no_formal_ino;

	error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, &gh);
	if (error)
		return error;

	error = gfs2_dir_read(dir, &gnfd.ctx, &f_ra);

	gfs2_glock_dq_uninit(&gh);

	if (!error && !*name)
		error = -ENOENT;

	return error;
}