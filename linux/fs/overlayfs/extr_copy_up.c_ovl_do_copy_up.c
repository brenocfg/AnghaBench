#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct ovl_fs {scalar_t__ tmpfile; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int nlink; int /*<<< orphan*/  mode; } ;
struct TYPE_11__ {int /*<<< orphan*/  dentry; } ;
struct ovl_copy_up_ctx {int indexed; int origin; TYPE_8__ destname; TYPE_3__* dentry; int /*<<< orphan*/  pstat; TYPE_3__* destdir; TYPE_2__ stat; int /*<<< orphan*/  parent; TYPE_1__ lowerpath; void* workdir; } ;
struct inode {int dummy; } ;
struct TYPE_14__ {struct ovl_fs* s_fs_info; } ;
struct TYPE_13__ {TYPE_7__* d_sb; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OVL_INDEX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct inode* d_inode (TYPE_3__*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int ovl_copy_up_tmpfile (struct ovl_copy_up_ctx*) ; 
 int ovl_copy_up_workdir (struct ovl_copy_up_ctx*) ; 
 int /*<<< orphan*/  ovl_dentry_set_upper_alias (TYPE_3__*) ; 
 int ovl_get_index_name (int /*<<< orphan*/ ,TYPE_8__*) ; 
 void* ovl_indexdir (TYPE_7__*) ; 
 scalar_t__ ovl_need_index (TYPE_3__*) ; 
 int /*<<< orphan*/  ovl_set_flag (int /*<<< orphan*/ ,struct inode*) ; 
 int ovl_set_impure (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int ovl_set_nlink_upper (TYPE_3__*) ; 
 int /*<<< orphan*/  ovl_set_timestamps (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovl_do_copy_up(struct ovl_copy_up_ctx *c)
{
	int err;
	struct ovl_fs *ofs = c->dentry->d_sb->s_fs_info;
	bool to_index = false;

	/*
	 * Indexed non-dir is copied up directly to the index entry and then
	 * hardlinked to upper dir. Indexed dir is copied up to indexdir,
	 * then index entry is created and then copied up dir installed.
	 * Copying dir up to indexdir instead of workdir simplifies locking.
	 */
	if (ovl_need_index(c->dentry)) {
		c->indexed = true;
		if (S_ISDIR(c->stat.mode))
			c->workdir = ovl_indexdir(c->dentry->d_sb);
		else
			to_index = true;
	}

	if (S_ISDIR(c->stat.mode) || c->stat.nlink == 1 || to_index)
		c->origin = true;

	if (to_index) {
		c->destdir = ovl_indexdir(c->dentry->d_sb);
		err = ovl_get_index_name(c->lowerpath.dentry, &c->destname);
		if (err)
			return err;
	} else if (WARN_ON(!c->parent)) {
		/* Disconnected dentry must be copied up to index dir */
		return -EIO;
	} else {
		/*
		 * Mark parent "impure" because it may now contain non-pure
		 * upper
		 */
		err = ovl_set_impure(c->parent, c->destdir);
		if (err)
			return err;
	}

	/* Should we copyup with O_TMPFILE or with workdir? */
	if (S_ISREG(c->stat.mode) && ofs->tmpfile)
		err = ovl_copy_up_tmpfile(c);
	else
		err = ovl_copy_up_workdir(c);
	if (err)
		goto out;

	if (c->indexed)
		ovl_set_flag(OVL_INDEX, d_inode(c->dentry));

	if (to_index) {
		/* Initialize nlink for copy up of disconnected dentry */
		err = ovl_set_nlink_upper(c->dentry);
	} else {
		struct inode *udir = d_inode(c->destdir);

		/* Restore timestamps on parent (best effort) */
		inode_lock(udir);
		ovl_set_timestamps(c->destdir, &c->pstat);
		inode_unlock(udir);

		ovl_dentry_set_upper_alias(c->dentry);
	}

out:
	if (to_index)
		kfree(c->destname.name);
	return err;
}