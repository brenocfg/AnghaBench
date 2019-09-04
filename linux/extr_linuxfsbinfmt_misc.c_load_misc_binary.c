#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct linux_binprm {int interp_flags; int interp_data; int /*<<< orphan*/  buf; struct file* file; int /*<<< orphan*/  argc; int /*<<< orphan*/  interp; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  dentry; int /*<<< orphan*/  interpreter; int /*<<< orphan*/  interp_file; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  BINPRM_BUF_SIZE ; 
 int BINPRM_FLAGS_EXECFD ; 
 int BINPRM_FLAGS_PATH_INACCESSIBLE ; 
 int ENOENT ; 
 int ENOEXEC ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int MISC_FMT_CREDENTIALS ; 
 int MISC_FMT_OPEN_BINARY ; 
 int MISC_FMT_OPEN_FILE ; 
 int MISC_FMT_PRESERVE_ARGV0 ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  allow_write_access (struct file*) ; 
 int bprm_change_interp (int /*<<< orphan*/ ,struct linux_binprm*) ; 
 TYPE_1__* check_file (struct linux_binprm*) ; 
 int copy_strings_kernel (int,int /*<<< orphan*/ *,struct linux_binprm*) ; 
 int /*<<< orphan*/  deny_write_access (struct file*) ; 
 int /*<<< orphan*/  dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enabled ; 
 int /*<<< orphan*/  entries_lock ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 struct file* file_clone_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int kernel_read (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksys_close (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct file* open_exec (int /*<<< orphan*/ ) ; 
 int prepare_binprm (struct linux_binprm*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int remove_arg_zero (struct linux_binprm*) ; 
 int search_binary_handler (struct linux_binprm*) ; 
 int /*<<< orphan*/  would_dump (struct linux_binprm*,struct file*) ; 

__attribute__((used)) static int load_misc_binary(struct linux_binprm *bprm)
{
	Node *fmt;
	struct file *interp_file = NULL;
	int retval;
	int fd_binary = -1;

	retval = -ENOEXEC;
	if (!enabled)
		return retval;

	/* to keep locking time low, we copy the interpreter string */
	read_lock(&entries_lock);
	fmt = check_file(bprm);
	if (fmt)
		dget(fmt->dentry);
	read_unlock(&entries_lock);
	if (!fmt)
		return retval;

	/* Need to be able to load the file after exec */
	retval = -ENOENT;
	if (bprm->interp_flags & BINPRM_FLAGS_PATH_INACCESSIBLE)
		goto ret;

	if (!(fmt->flags & MISC_FMT_PRESERVE_ARGV0)) {
		retval = remove_arg_zero(bprm);
		if (retval)
			goto ret;
	}

	if (fmt->flags & MISC_FMT_OPEN_BINARY) {

		/* if the binary should be opened on behalf of the
		 * interpreter than keep it open and assign descriptor
		 * to it
		 */
		fd_binary = get_unused_fd_flags(0);
		if (fd_binary < 0) {
			retval = fd_binary;
			goto ret;
		}
		fd_install(fd_binary, bprm->file);

		/* if the binary is not readable than enforce mm->dumpable=0
		   regardless of the interpreter's permissions */
		would_dump(bprm, bprm->file);

		allow_write_access(bprm->file);
		bprm->file = NULL;

		/* mark the bprm that fd should be passed to interp */
		bprm->interp_flags |= BINPRM_FLAGS_EXECFD;
		bprm->interp_data = fd_binary;

	} else {
		allow_write_access(bprm->file);
		fput(bprm->file);
		bprm->file = NULL;
	}
	/* make argv[1] be the path to the binary */
	retval = copy_strings_kernel(1, &bprm->interp, bprm);
	if (retval < 0)
		goto error;
	bprm->argc++;

	/* add the interp as argv[0] */
	retval = copy_strings_kernel(1, &fmt->interpreter, bprm);
	if (retval < 0)
		goto error;
	bprm->argc++;

	/* Update interp in case binfmt_script needs it. */
	retval = bprm_change_interp(fmt->interpreter, bprm);
	if (retval < 0)
		goto error;

	if (fmt->flags & MISC_FMT_OPEN_FILE) {
		interp_file = file_clone_open(fmt->interp_file);
		if (!IS_ERR(interp_file))
			deny_write_access(interp_file);
	} else {
		interp_file = open_exec(fmt->interpreter);
	}
	retval = PTR_ERR(interp_file);
	if (IS_ERR(interp_file))
		goto error;

	bprm->file = interp_file;
	if (fmt->flags & MISC_FMT_CREDENTIALS) {
		loff_t pos = 0;

		/*
		 * No need to call prepare_binprm(), it's already been
		 * done.  bprm->buf is stale, update from interp_file.
		 */
		memset(bprm->buf, 0, BINPRM_BUF_SIZE);
		retval = kernel_read(bprm->file, bprm->buf, BINPRM_BUF_SIZE,
				&pos);
	} else
		retval = prepare_binprm(bprm);

	if (retval < 0)
		goto error;

	retval = search_binary_handler(bprm);
	if (retval < 0)
		goto error;

ret:
	dput(fmt->dentry);
	return retval;
error:
	if (fd_binary > 0)
		ksys_close(fd_binary);
	bprm->interp_flags = 0;
	bprm->interp_data = 0;
	goto ret;
}