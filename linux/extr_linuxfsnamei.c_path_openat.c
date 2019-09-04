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
struct open_flags {int /*<<< orphan*/  open_flag; } ;
struct nameidata {int flags; } ;
struct file {int f_flags; int f_mode; } ;

/* Variables and functions */
 int ECHILD ; 
 int EINVAL ; 
 int EOPENSTALE ; 
 struct file* ERR_PTR (int) ; 
 int ESTALE ; 
 int FMODE_OPENED ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int LOOKUP_CREATE ; 
 int LOOKUP_EXCL ; 
 int LOOKUP_OPEN ; 
 unsigned int LOOKUP_RCU ; 
 int O_PATH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __O_TMPFILE ; 
 struct file* alloc_empty_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_cred () ; 
 int do_last (struct nameidata*,struct file*,struct open_flags const*) ; 
 int do_o_path (struct nameidata*,unsigned int,struct file*) ; 
 int do_tmpfile (struct nameidata*,unsigned int,struct open_flags const*,struct file*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 scalar_t__ likely (int) ; 
 int link_path_walk (char const*,struct nameidata*) ; 
 char* path_init (struct nameidata*,unsigned int) ; 
 int /*<<< orphan*/  terminate_walk (struct nameidata*) ; 
 char* trailing_symlink (struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct file *path_openat(struct nameidata *nd,
			const struct open_flags *op, unsigned flags)
{
	struct file *file;
	int error;

	file = alloc_empty_file(op->open_flag, current_cred());
	if (IS_ERR(file))
		return file;

	if (unlikely(file->f_flags & __O_TMPFILE)) {
		error = do_tmpfile(nd, flags, op, file);
	} else if (unlikely(file->f_flags & O_PATH)) {
		error = do_o_path(nd, flags, file);
	} else {
		const char *s = path_init(nd, flags);
		while (!(error = link_path_walk(s, nd)) &&
			(error = do_last(nd, file, op)) > 0) {
			nd->flags &= ~(LOOKUP_OPEN|LOOKUP_CREATE|LOOKUP_EXCL);
			s = trailing_symlink(nd);
		}
		terminate_walk(nd);
	}
	if (likely(!error)) {
		if (likely(file->f_mode & FMODE_OPENED))
			return file;
		WARN_ON(1);
		error = -EINVAL;
	}
	fput(file);
	if (error == -EOPENSTALE) {
		if (flags & LOOKUP_RCU)
			error = -ECHILD;
		else
			error = -ESTALE;
	}
	return ERR_PTR(error);
}