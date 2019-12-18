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
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct kstat {int /*<<< orphan*/  ino; } ;
struct inode {int /*<<< orphan*/  i_fop; int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  actor; } ;
struct getdents_callback {char* name; int sequence; scalar_t__ found; TYPE_2__ ctx; int /*<<< orphan*/  ino; } ;
struct file {TYPE_1__* f_op; } ;
struct dentry {struct inode* d_inode; } ;
struct cred {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  iterate_shared; int /*<<< orphan*/  iterate; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_STATX_SYNC_AS_STAT ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOTDIR ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  STATX_INO ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 struct file* dentry_open (struct path const*,int /*<<< orphan*/ ,struct cred const*) ; 
 int /*<<< orphan*/  filldir_one ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int iterate_dir (struct file*,TYPE_2__*) ; 
 int vfs_getattr_nosec (struct path*,struct kstat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_name(const struct path *path, char *name, struct dentry *child)
{
	const struct cred *cred = current_cred();
	struct inode *dir = path->dentry->d_inode;
	int error;
	struct file *file;
	struct kstat stat;
	struct path child_path = {
		.mnt = path->mnt,
		.dentry = child,
	};
	struct getdents_callback buffer = {
		.ctx.actor = filldir_one,
		.name = name,
	};

	error = -ENOTDIR;
	if (!dir || !S_ISDIR(dir->i_mode))
		goto out;
	error = -EINVAL;
	if (!dir->i_fop)
		goto out;
	/*
	 * inode->i_ino is unsigned long, kstat->ino is u64, so the
	 * former would be insufficient on 32-bit hosts when the
	 * filesystem supports 64-bit inode numbers.  So we need to
	 * actually call ->getattr, not just read i_ino:
	 */
	error = vfs_getattr_nosec(&child_path, &stat,
				  STATX_INO, AT_STATX_SYNC_AS_STAT);
	if (error)
		return error;
	buffer.ino = stat.ino;
	/*
	 * Open the directory ...
	 */
	file = dentry_open(path, O_RDONLY, cred);
	error = PTR_ERR(file);
	if (IS_ERR(file))
		goto out;

	error = -EINVAL;
	if (!file->f_op->iterate && !file->f_op->iterate_shared)
		goto out_close;

	buffer.sequence = 0;
	while (1) {
		int old_seq = buffer.sequence;

		error = iterate_dir(file, &buffer.ctx);
		if (buffer.found) {
			error = 0;
			break;
		}

		if (error < 0)
			break;

		error = -ENOENT;
		if (old_seq == buffer.sequence)
			break;
	}

out_close:
	fput(file);
out:
	return error;
}