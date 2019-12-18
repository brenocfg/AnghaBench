#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_5__* i_mapping; int /*<<< orphan*/  i_fop; int /*<<< orphan*/  i_mode; } ;
struct file_operations {int (* open ) (struct inode*,struct file*) ;scalar_t__ write_iter; scalar_t__ write; scalar_t__ read_iter; scalar_t__ read; } ;
struct TYPE_9__ {int /*<<< orphan*/ * dentry; int /*<<< orphan*/ * mnt; } ;
struct file {int f_flags; int f_mode; struct inode* f_inode; TYPE_3__ f_path; struct file_operations const* f_op; TYPE_5__* f_mapping; int /*<<< orphan*/  f_ra; int /*<<< orphan*/  f_write_hint; int /*<<< orphan*/  f_wb_err; } ;
struct TYPE_10__ {TYPE_2__* a_ops; TYPE_1__* host; } ;
struct TYPE_8__ {int /*<<< orphan*/  direct_IO; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENODEV ; 
 int FMODE_ATOMIC_POS ; 
 int FMODE_CAN_READ ; 
 int FMODE_CAN_WRITE ; 
 int FMODE_EXEC ; 
 int FMODE_LSEEK ; 
 int FMODE_OPENED ; 
 int FMODE_PATH ; 
 int FMODE_PREAD ; 
 int FMODE_PWRITE ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int FMODE_WRITER ; 
 int O_CREAT ; 
 int O_DIRECT ; 
 int O_EXCL ; 
 int O_NOCTTY ; 
 int O_PATH ; 
 int O_TRUNC ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_LIFE_NOT_SET ; 
 int /*<<< orphan*/  __mnt_drop_write (int /*<<< orphan*/ *) ; 
 int __mnt_want_write (int /*<<< orphan*/ *) ; 
 int break_lease (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  file_ra_state_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ filemap_nr_thps (TYPE_5__*) ; 
 int /*<<< orphan*/  filemap_sample_wb_err (TYPE_5__*) ; 
 struct file_operations const* fops_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fops_put (struct file_operations const*) ; 
 int get_write_access (struct inode*) ; 
 int /*<<< orphan*/  i_readcount_inc (struct inode*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  locks_inode (struct file*) ; 
 int /*<<< orphan*/  path_get (TYPE_3__*) ; 
 int /*<<< orphan*/  path_put (TYPE_3__*) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 
 int security_file_open (struct file*) ; 
 int /*<<< orphan*/  special_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_dentry_open(struct file *f,
			  struct inode *inode,
			  int (*open)(struct inode *, struct file *))
{
	static const struct file_operations empty_fops = {};
	int error;

	path_get(&f->f_path);
	f->f_inode = inode;
	f->f_mapping = inode->i_mapping;

	/* Ensure that we skip any errors that predate opening of the file */
	f->f_wb_err = filemap_sample_wb_err(f->f_mapping);

	if (unlikely(f->f_flags & O_PATH)) {
		f->f_mode = FMODE_PATH | FMODE_OPENED;
		f->f_op = &empty_fops;
		return 0;
	}

	/* Any file opened for execve()/uselib() has to be a regular file. */
	if (unlikely(f->f_flags & FMODE_EXEC && !S_ISREG(inode->i_mode))) {
		error = -EACCES;
		goto cleanup_file;
	}

	if (f->f_mode & FMODE_WRITE && !special_file(inode->i_mode)) {
		error = get_write_access(inode);
		if (unlikely(error))
			goto cleanup_file;
		error = __mnt_want_write(f->f_path.mnt);
		if (unlikely(error)) {
			put_write_access(inode);
			goto cleanup_file;
		}
		f->f_mode |= FMODE_WRITER;
	}

	/* POSIX.1-2008/SUSv4 Section XSI 2.9.7 */
	if (S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode))
		f->f_mode |= FMODE_ATOMIC_POS;

	f->f_op = fops_get(inode->i_fop);
	if (WARN_ON(!f->f_op)) {
		error = -ENODEV;
		goto cleanup_all;
	}

	error = security_file_open(f);
	if (error)
		goto cleanup_all;

	error = break_lease(locks_inode(f), f->f_flags);
	if (error)
		goto cleanup_all;

	/* normally all 3 are set; ->open() can clear them if needed */
	f->f_mode |= FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE;
	if (!open)
		open = f->f_op->open;
	if (open) {
		error = open(inode, f);
		if (error)
			goto cleanup_all;
	}
	f->f_mode |= FMODE_OPENED;
	if ((f->f_mode & (FMODE_READ | FMODE_WRITE)) == FMODE_READ)
		i_readcount_inc(inode);
	if ((f->f_mode & FMODE_READ) &&
	     likely(f->f_op->read || f->f_op->read_iter))
		f->f_mode |= FMODE_CAN_READ;
	if ((f->f_mode & FMODE_WRITE) &&
	     likely(f->f_op->write || f->f_op->write_iter))
		f->f_mode |= FMODE_CAN_WRITE;

	f->f_write_hint = WRITE_LIFE_NOT_SET;
	f->f_flags &= ~(O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC);

	file_ra_state_init(&f->f_ra, f->f_mapping->host->i_mapping);

	/* NB: we're sure to have correct a_ops only after f_op->open */
	if (f->f_flags & O_DIRECT) {
		if (!f->f_mapping->a_ops || !f->f_mapping->a_ops->direct_IO)
			return -EINVAL;
	}

	/*
	 * XXX: Huge page cache doesn't support writing yet. Drop all page
	 * cache for this file before processing writes.
	 */
	if ((f->f_mode & FMODE_WRITE) && filemap_nr_thps(inode->i_mapping))
		truncate_pagecache(inode, 0);

	return 0;

cleanup_all:
	if (WARN_ON_ONCE(error > 0))
		error = -EINVAL;
	fops_put(f->f_op);
	if (f->f_mode & FMODE_WRITER) {
		put_write_access(inode);
		__mnt_drop_write(f->f_path.mnt);
	}
cleanup_file:
	path_put(&f->f_path);
	f->f_path.mnt = NULL;
	f->f_path.dentry = NULL;
	f->f_inode = NULL;
	return error;
}