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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  d_name; } ;
struct gfs2_holder {int dummy; } ;
struct gfs2_glock {int dummy; } ;
struct file {int dummy; } ;
struct dentry {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {struct gfs2_glock* i_gl; } ;

/* Variables and functions */
 struct inode* ERR_CAST (struct inode*) ; 
 struct inode* ERR_PTR (int) ; 
 TYPE_1__* GFS2_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  LM_FLAG_ANY ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_add (struct inode*,int /*<<< orphan*/ *) ; 
 struct inode* d_splice_alias (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  dput (struct inode*) ; 
 int finish_open (struct file*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (struct gfs2_glock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 struct inode* gfs2_lookupi (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_open_common ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static struct dentry *__gfs2_lookup(struct inode *dir, struct dentry *dentry,
				    struct file *file)
{
	struct inode *inode;
	struct dentry *d;
	struct gfs2_holder gh;
	struct gfs2_glock *gl;
	int error;

	inode = gfs2_lookupi(dir, &dentry->d_name, 0);
	if (inode == NULL) {
		d_add(dentry, NULL);
		return NULL;
	}
	if (IS_ERR(inode))
		return ERR_CAST(inode);

	gl = GFS2_I(inode)->i_gl;
	error = gfs2_glock_nq_init(gl, LM_ST_SHARED, LM_FLAG_ANY, &gh);
	if (error) {
		iput(inode);
		return ERR_PTR(error);
	}

	d = d_splice_alias(inode, dentry);
	if (IS_ERR(d)) {
		gfs2_glock_dq_uninit(&gh);
		return d;
	}
	if (file && S_ISREG(inode->i_mode))
		error = finish_open(file, dentry, gfs2_open_common);

	gfs2_glock_dq_uninit(&gh);
	if (error) {
		dput(d);
		return ERR_PTR(error);
	}
	return d;
}