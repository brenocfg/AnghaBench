#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct inode {int i_mode; int /*<<< orphan*/  i_ino; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; struct ceph_dir_file_info* private_data; } ;
struct dir_context {int pos; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_3__ d_name; int /*<<< orphan*/  d_sb; int /*<<< orphan*/  d_lock; } ;
struct ceph_readdir_cache_control {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct ceph_dir_file_info {int readdir_cache_idx; scalar_t__ dir_release_count; TYPE_2__ file_info; } ;
struct ceph_dentry_info {int offset; int lease_shared_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_F_ATEND ; 
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  __ceph_dentry_dir_lease_touch (struct ceph_dentry_info*) ; 
 struct dentry* __dcache_find_get_entry (struct dentry*,int,struct ceph_readdir_cache_control*) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 int /*<<< orphan*/  ceph_readdir_cache_release (struct ceph_readdir_cache_control*) ; 
 int /*<<< orphan*/  ceph_translate_ino (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int div_u64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 scalar_t__ fpos_cmp (int,int) ; 
 scalar_t__ fpos_off (int) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int note_last_dentry (struct ceph_dir_file_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __dcache_readdir(struct file *file,  struct dir_context *ctx,
			    int shared_gen)
{
	struct ceph_dir_file_info *dfi = file->private_data;
	struct dentry *parent = file->f_path.dentry;
	struct inode *dir = d_inode(parent);
	struct dentry *dentry, *last = NULL;
	struct ceph_dentry_info *di;
	struct ceph_readdir_cache_control cache_ctl = {};
	u64 idx = 0;
	int err = 0;

	dout("__dcache_readdir %p v%u at %llx\n", dir, (unsigned)shared_gen, ctx->pos);

	/* search start position */
	if (ctx->pos > 2) {
		u64 count = div_u64(i_size_read(dir), sizeof(struct dentry *));
		while (count > 0) {
			u64 step = count >> 1;
			dentry = __dcache_find_get_entry(parent, idx + step,
							 &cache_ctl);
			if (!dentry) {
				/* use linar search */
				idx = 0;
				break;
			}
			if (IS_ERR(dentry)) {
				err = PTR_ERR(dentry);
				goto out;
			}
			di = ceph_dentry(dentry);
			spin_lock(&dentry->d_lock);
			if (fpos_cmp(di->offset, ctx->pos) < 0) {
				idx += step + 1;
				count -= step + 1;
			} else {
				count = step;
			}
			spin_unlock(&dentry->d_lock);
			dput(dentry);
		}

		dout("__dcache_readdir %p cache idx %llu\n", dir, idx);
	}


	for (;;) {
		bool emit_dentry = false;
		dentry = __dcache_find_get_entry(parent, idx++, &cache_ctl);
		if (!dentry) {
			dfi->file_info.flags |= CEPH_F_ATEND;
			err = 0;
			break;
		}
		if (IS_ERR(dentry)) {
			err = PTR_ERR(dentry);
			goto out;
		}

		spin_lock(&dentry->d_lock);
		di = ceph_dentry(dentry);
		if (d_unhashed(dentry) ||
		    d_really_is_negative(dentry) ||
		    di->lease_shared_gen != shared_gen) {
			spin_unlock(&dentry->d_lock);
			dput(dentry);
			err = -EAGAIN;
			goto out;
		}
		if (fpos_cmp(ctx->pos, di->offset) <= 0) {
			__ceph_dentry_dir_lease_touch(di);
			emit_dentry = true;
		}
		spin_unlock(&dentry->d_lock);

		if (emit_dentry) {
			dout(" %llx dentry %p %pd %p\n", di->offset,
			     dentry, dentry, d_inode(dentry));
			ctx->pos = di->offset;
			if (!dir_emit(ctx, dentry->d_name.name,
				      dentry->d_name.len,
				      ceph_translate_ino(dentry->d_sb,
							 d_inode(dentry)->i_ino),
				      d_inode(dentry)->i_mode >> 12)) {
				dput(dentry);
				err = 0;
				break;
			}
			ctx->pos++;

			if (last)
				dput(last);
			last = dentry;
		} else {
			dput(dentry);
		}
	}
out:
	ceph_readdir_cache_release(&cache_ctl);
	if (last) {
		int ret;
		di = ceph_dentry(last);
		ret = note_last_dentry(dfi, last->d_name.name, last->d_name.len,
				       fpos_off(di->offset) + 1);
		if (ret < 0)
			err = ret;
		dput(last);
		/* last_name no longer match cache index */
		if (dfi->readdir_cache_idx >= 0) {
			dfi->readdir_cache_idx = -1;
			dfi->dir_release_count = 0;
		}
	}
	return err;
}