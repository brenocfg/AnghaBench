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
struct path {struct dentry* dentry; } ;
struct TYPE_4__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  actor; } ;
struct ovl_readdir_translate {TYPE_2__ ctx; int /*<<< orphan*/  cache; int /*<<< orphan*/  parent_ino; int /*<<< orphan*/  fsid; scalar_t__ xinobits; struct dir_context* orig_ctx; } ;
struct ovl_layer {int /*<<< orphan*/  fsid; } ;
struct ovl_dir_file {int /*<<< orphan*/  realfile; } ;
struct kstat {scalar_t__ dev; int /*<<< orphan*/  ino; } ;
struct file {struct path f_path; struct ovl_dir_file* private_data; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;
struct dentry {TYPE_1__* d_sb; struct dentry* d_parent; } ;
struct TYPE_3__ {scalar_t__ s_dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ OVL_TYPE_MERGE (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATX_INO ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int iterate_dir (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ovl_cache_get_impure (struct path*) ; 
 int /*<<< orphan*/  ovl_fill_real ; 
 scalar_t__ ovl_is_impure_dir (struct file*) ; 
 struct ovl_layer* ovl_layer_lower (struct dentry*) ; 
 int /*<<< orphan*/  ovl_path_type (struct dentry*) ; 
 scalar_t__ ovl_xino_bits (TYPE_1__*) ; 
 int vfs_getattr (struct path*,struct kstat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_iterate_real(struct file *file, struct dir_context *ctx)
{
	int err;
	struct ovl_dir_file *od = file->private_data;
	struct dentry *dir = file->f_path.dentry;
	struct ovl_layer *lower_layer = ovl_layer_lower(dir);
	struct ovl_readdir_translate rdt = {
		.ctx.actor = ovl_fill_real,
		.orig_ctx = ctx,
		.xinobits = ovl_xino_bits(dir->d_sb),
	};

	if (rdt.xinobits && lower_layer)
		rdt.fsid = lower_layer->fsid;

	if (OVL_TYPE_MERGE(ovl_path_type(dir->d_parent))) {
		struct kstat stat;
		struct path statpath = file->f_path;

		statpath.dentry = dir->d_parent;
		err = vfs_getattr(&statpath, &stat, STATX_INO, 0);
		if (err)
			return err;

		WARN_ON_ONCE(dir->d_sb->s_dev != stat.dev);
		rdt.parent_ino = stat.ino;
	}

	if (ovl_is_impure_dir(file)) {
		rdt.cache = ovl_cache_get_impure(&file->f_path);
		if (IS_ERR(rdt.cache))
			return PTR_ERR(rdt.cache);
	}

	err = iterate_dir(od->realfile, &rdt.ctx);
	ctx->pos = rdt.ctx.pos;

	return err;
}