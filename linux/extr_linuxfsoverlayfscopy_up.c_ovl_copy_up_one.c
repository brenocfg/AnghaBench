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
struct path {int /*<<< orphan*/  dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; scalar_t__ size; } ;
struct ovl_copy_up_ctx {int /*<<< orphan*/  link; struct path lowerpath; TYPE_1__ stat; TYPE_1__ pstat; int /*<<< orphan*/  destname; int /*<<< orphan*/  destdir; int /*<<< orphan*/  metacopy; int /*<<< orphan*/  workdir; struct dentry* dentry; struct dentry* parent; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_STATX_SYNC_AS_STAT ; 
 int /*<<< orphan*/  DEFINE_DELAYED_CALL (int /*<<< orphan*/ ) ; 
 int EROFS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int O_TRUNC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int STATX_ATIME ; 
 int STATX_BASIC_STATS ; 
 int STATX_MTIME ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  do_delayed_call (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  ovl_copy_up_end (struct dentry*) ; 
 int ovl_copy_up_meta_inode_data (struct ovl_copy_up_ctx*) ; 
 int ovl_copy_up_start (struct dentry*,int) ; 
 int /*<<< orphan*/  ovl_dentry_has_upper_alias (struct dentry*) ; 
 scalar_t__ ovl_dentry_needs_data_copy_up_locked (struct dentry*,int) ; 
 int /*<<< orphan*/  ovl_dentry_upper (struct dentry*) ; 
 int ovl_do_copy_up (struct ovl_copy_up_ctx*) ; 
 int ovl_link_up (struct ovl_copy_up_ctx*) ; 
 int /*<<< orphan*/  ovl_need_meta_copy_up (struct dentry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ovl_path_lower (struct dentry*,struct path*) ; 
 int /*<<< orphan*/  ovl_path_upper (struct dentry*,struct path*) ; 
 int /*<<< orphan*/  ovl_workdir (struct dentry*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vfs_get_link (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vfs_getattr (struct path*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_copy_up_one(struct dentry *parent, struct dentry *dentry,
			   int flags)
{
	int err;
	DEFINE_DELAYED_CALL(done);
	struct path parentpath;
	struct ovl_copy_up_ctx ctx = {
		.parent = parent,
		.dentry = dentry,
		.workdir = ovl_workdir(dentry),
	};

	if (WARN_ON(!ctx.workdir))
		return -EROFS;

	ovl_path_lower(dentry, &ctx.lowerpath);
	err = vfs_getattr(&ctx.lowerpath, &ctx.stat,
			  STATX_BASIC_STATS, AT_STATX_SYNC_AS_STAT);
	if (err)
		return err;

	ctx.metacopy = ovl_need_meta_copy_up(dentry, ctx.stat.mode, flags);

	if (parent) {
		ovl_path_upper(parent, &parentpath);
		ctx.destdir = parentpath.dentry;
		ctx.destname = dentry->d_name;

		err = vfs_getattr(&parentpath, &ctx.pstat,
				  STATX_ATIME | STATX_MTIME,
				  AT_STATX_SYNC_AS_STAT);
		if (err)
			return err;
	}

	/* maybe truncate regular file. this has no effect on dirs */
	if (flags & O_TRUNC)
		ctx.stat.size = 0;

	if (S_ISLNK(ctx.stat.mode)) {
		ctx.link = vfs_get_link(ctx.lowerpath.dentry, &done);
		if (IS_ERR(ctx.link))
			return PTR_ERR(ctx.link);
	}

	err = ovl_copy_up_start(dentry, flags);
	/* err < 0: interrupted, err > 0: raced with another copy-up */
	if (unlikely(err)) {
		if (err > 0)
			err = 0;
	} else {
		if (!ovl_dentry_upper(dentry))
			err = ovl_do_copy_up(&ctx);
		if (!err && parent && !ovl_dentry_has_upper_alias(dentry))
			err = ovl_link_up(&ctx);
		if (!err && ovl_dentry_needs_data_copy_up_locked(dentry, flags))
			err = ovl_copy_up_meta_inode_data(&ctx);
		ovl_copy_up_end(dentry);
	}
	do_delayed_call(&done);

	return err;
}