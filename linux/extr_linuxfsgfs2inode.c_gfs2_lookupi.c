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
struct super_block {int /*<<< orphan*/  s_root; } ;
struct qstr {int len; int /*<<< orphan*/  name; } ;
struct inode {struct super_block* i_sb; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOENT ; 
 struct inode* ERR_PTR (int) ; 
 int GFS2_FNAMESIZE ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 int PTR_ERR (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 struct inode* gfs2_dir_search (struct inode*,struct qstr const*,int) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/ * gfs2_glock_is_locked_by_me (int /*<<< orphan*/ ) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ gfs2_holder_initialized (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_mark_uninitialized (struct gfs2_holder*) ; 
 int gfs2_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

struct inode *gfs2_lookupi(struct inode *dir, const struct qstr *name,
			   int is_root)
{
	struct super_block *sb = dir->i_sb;
	struct gfs2_inode *dip = GFS2_I(dir);
	struct gfs2_holder d_gh;
	int error = 0;
	struct inode *inode = NULL;

	gfs2_holder_mark_uninitialized(&d_gh);
	if (!name->len || name->len > GFS2_FNAMESIZE)
		return ERR_PTR(-ENAMETOOLONG);

	if ((name->len == 1 && memcmp(name->name, ".", 1) == 0) ||
	    (name->len == 2 && memcmp(name->name, "..", 2) == 0 &&
	     dir == d_inode(sb->s_root))) {
		igrab(dir);
		return dir;
	}

	if (gfs2_glock_is_locked_by_me(dip->i_gl) == NULL) {
		error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, &d_gh);
		if (error)
			return ERR_PTR(error);
	}

	if (!is_root) {
		error = gfs2_permission(dir, MAY_EXEC);
		if (error)
			goto out;
	}

	inode = gfs2_dir_search(dir, name, false);
	if (IS_ERR(inode))
		error = PTR_ERR(inode);
out:
	if (gfs2_holder_initialized(&d_gh))
		gfs2_glock_dq_uninit(&d_gh);
	if (error == -ENOENT)
		return NULL;
	return inode ? inode : ERR_PTR(error);
}