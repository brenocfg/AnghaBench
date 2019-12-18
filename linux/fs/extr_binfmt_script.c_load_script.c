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
struct linux_binprm {char* buf; int interp_flags; char const* interp; struct file* file; int /*<<< orphan*/  argc; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int BINPRM_FLAGS_PATH_INACCESSIBLE ; 
 int ENOENT ; 
 int ENOEXEC ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  allow_write_access (struct file*) ; 
 int bprm_change_interp (char const*,struct linux_binprm*) ; 
 int copy_strings_kernel (int,char const**,struct linux_binprm*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 char* next_non_spacetab (char*,char*) ; 
 int /*<<< orphan*/  next_terminator (char*,char*) ; 
 struct file* open_exec (char const*) ; 
 int prepare_binprm (struct linux_binprm*) ; 
 int remove_arg_zero (struct linux_binprm*) ; 
 int search_binary_handler (struct linux_binprm*) ; 
 char* strnchr (char*,int,char) ; 

__attribute__((used)) static int load_script(struct linux_binprm *bprm)
{
	const char *i_arg, *i_name;
	char *cp, *buf_end;
	struct file *file;
	int retval;

	/* Not ours to exec if we don't start with "#!". */
	if ((bprm->buf[0] != '#') || (bprm->buf[1] != '!'))
		return -ENOEXEC;

	/*
	 * If the script filename will be inaccessible after exec, typically
	 * because it is a "/dev/fd/<fd>/.." path against an O_CLOEXEC fd, give
	 * up now (on the assumption that the interpreter will want to load
	 * this file).
	 */
	if (bprm->interp_flags & BINPRM_FLAGS_PATH_INACCESSIBLE)
		return -ENOENT;

	/* Release since we are not mapping a binary into memory. */
	allow_write_access(bprm->file);
	fput(bprm->file);
	bprm->file = NULL;

	/*
	 * This section handles parsing the #! line into separate
	 * interpreter path and argument strings. We must be careful
	 * because bprm->buf is not yet guaranteed to be NUL-terminated
	 * (though the buffer will have trailing NUL padding when the
	 * file size was smaller than the buffer size).
	 *
	 * We do not want to exec a truncated interpreter path, so either
	 * we find a newline (which indicates nothing is truncated), or
	 * we find a space/tab/NUL after the interpreter path (which
	 * itself may be preceded by spaces/tabs). Truncating the
	 * arguments is fine: the interpreter can re-read the script to
	 * parse them on its own.
	 */
	buf_end = bprm->buf + sizeof(bprm->buf) - 1;
	cp = strnchr(bprm->buf, sizeof(bprm->buf), '\n');
	if (!cp) {
		cp = next_non_spacetab(bprm->buf + 2, buf_end);
		if (!cp)
			return -ENOEXEC; /* Entire buf is spaces/tabs */
		/*
		 * If there is no later space/tab/NUL we must assume the
		 * interpreter path is truncated.
		 */
		if (!next_terminator(cp, buf_end))
			return -ENOEXEC;
		cp = buf_end;
	}
	/* NUL-terminate the buffer and any trailing spaces/tabs. */
	*cp = '\0';
	while (cp > bprm->buf) {
		cp--;
		if ((*cp == ' ') || (*cp == '\t'))
			*cp = '\0';
		else
			break;
	}
	for (cp = bprm->buf+2; (*cp == ' ') || (*cp == '\t'); cp++);
	if (*cp == '\0')
		return -ENOEXEC; /* No interpreter name found */
	i_name = cp;
	i_arg = NULL;
	for ( ; *cp && (*cp != ' ') && (*cp != '\t'); cp++)
		/* nothing */ ;
	while ((*cp == ' ') || (*cp == '\t'))
		*cp++ = '\0';
	if (*cp)
		i_arg = cp;
	/*
	 * OK, we've parsed out the interpreter name and
	 * (optional) argument.
	 * Splice in (1) the interpreter's name for argv[0]
	 *           (2) (optional) argument to interpreter
	 *           (3) filename of shell script (replace argv[0])
	 *
	 * This is done in reverse order, because of how the
	 * user environment and arguments are stored.
	 */
	retval = remove_arg_zero(bprm);
	if (retval)
		return retval;
	retval = copy_strings_kernel(1, &bprm->interp, bprm);
	if (retval < 0)
		return retval;
	bprm->argc++;
	if (i_arg) {
		retval = copy_strings_kernel(1, &i_arg, bprm);
		if (retval < 0)
			return retval;
		bprm->argc++;
	}
	retval = copy_strings_kernel(1, &i_name, bprm);
	if (retval)
		return retval;
	bprm->argc++;
	retval = bprm_change_interp(i_name, bprm);
	if (retval < 0)
		return retval;

	/*
	 * OK, now restart the process with the interpreter's dentry.
	 */
	file = open_exec(i_name);
	if (IS_ERR(file))
		return PTR_ERR(file);

	bprm->file = file;
	retval = prepare_binprm(bprm);
	if (retval < 0)
		return retval;
	return search_binary_handler(bprm);
}