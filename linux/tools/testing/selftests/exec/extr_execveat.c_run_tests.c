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

/* Variables and functions */
 int AT_EMPTY_PATH ; 
 int AT_FDCWD ; 
 int AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ELOOP ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  ENOTDIR ; 
 int O_CLOEXEC ; 
 int O_DIRECTORY ; 
 int O_PATH ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ check_execveat (int,char*,int) ; 
 scalar_t__ check_execveat_fail (int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ check_execveat_pathmax (int,char*,int) ; 
 char* concat (char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execveat_ (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 int open_or_die (char*,int) ; 
 char* realpath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int run_tests(void)
{
	int fail = 0;
	char *fullname = realpath("execveat", NULL);
	char *fullname_script = realpath("script", NULL);
	char *fullname_symlink = concat(fullname, ".symlink");
	int subdir_dfd = open_or_die("subdir", O_DIRECTORY|O_RDONLY);
	int subdir_dfd_ephemeral = open_or_die("subdir.ephemeral",
					       O_DIRECTORY|O_RDONLY);
	int dot_dfd = open_or_die(".", O_DIRECTORY|O_RDONLY);
	int root_dfd = open_or_die("/", O_DIRECTORY|O_RDONLY);
	int dot_dfd_path = open_or_die(".", O_DIRECTORY|O_RDONLY|O_PATH);
	int dot_dfd_cloexec = open_or_die(".", O_DIRECTORY|O_RDONLY|O_CLOEXEC);
	int fd = open_or_die("execveat", O_RDONLY);
	int fd_path = open_or_die("execveat", O_RDONLY|O_PATH);
	int fd_symlink = open_or_die("execveat.symlink", O_RDONLY);
	int fd_denatured = open_or_die("execveat.denatured", O_RDONLY);
	int fd_denatured_path = open_or_die("execveat.denatured",
					    O_RDONLY|O_PATH);
	int fd_script = open_or_die("script", O_RDONLY);
	int fd_ephemeral = open_or_die("execveat.ephemeral", O_RDONLY);
	int fd_ephemeral_path = open_or_die("execveat.path.ephemeral",
					    O_RDONLY|O_PATH);
	int fd_script_ephemeral = open_or_die("script.ephemeral", O_RDONLY);
	int fd_cloexec = open_or_die("execveat", O_RDONLY|O_CLOEXEC);
	int fd_script_cloexec = open_or_die("script", O_RDONLY|O_CLOEXEC);

	/* Check if we have execveat at all, and bail early if not */
	errno = 0;
	execveat_(-1, NULL, NULL, NULL, 0);
	if (errno == ENOSYS) {
		ksft_exit_skip(
			"ENOSYS calling execveat - no kernel support?\n");
	}

	/* Change file position to confirm it doesn't affect anything */
	lseek(fd, 10, SEEK_SET);

	/* Normal executable file: */
	/*   dfd + path */
	fail += check_execveat(subdir_dfd, "../execveat", 0);
	fail += check_execveat(dot_dfd, "execveat", 0);
	fail += check_execveat(dot_dfd_path, "execveat", 0);
	/*   absolute path */
	fail += check_execveat(AT_FDCWD, fullname, 0);
	/*   absolute path with nonsense dfd */
	fail += check_execveat(99, fullname, 0);
	/*   fd + no path */
	fail += check_execveat(fd, "", AT_EMPTY_PATH);
	/*   O_CLOEXEC fd + no path */
	fail += check_execveat(fd_cloexec, "", AT_EMPTY_PATH);
	/*   O_PATH fd */
	fail += check_execveat(fd_path, "", AT_EMPTY_PATH);

	/* Mess with executable file that's already open: */
	/*   fd + no path to a file that's been renamed */
	rename("execveat.ephemeral", "execveat.moved");
	fail += check_execveat(fd_ephemeral, "", AT_EMPTY_PATH);
	/*   fd + no path to a file that's been deleted */
	unlink("execveat.moved"); /* remove the file now fd open */
	fail += check_execveat(fd_ephemeral, "", AT_EMPTY_PATH);

	/* Mess with executable file that's already open with O_PATH */
	/*   fd + no path to a file that's been deleted */
	unlink("execveat.path.ephemeral");
	fail += check_execveat(fd_ephemeral_path, "", AT_EMPTY_PATH);

	/* Invalid argument failures */
	fail += check_execveat_fail(fd, "", 0, ENOENT);
	fail += check_execveat_fail(fd, NULL, AT_EMPTY_PATH, EFAULT);

	/* Symlink to executable file: */
	/*   dfd + path */
	fail += check_execveat(dot_dfd, "execveat.symlink", 0);
	fail += check_execveat(dot_dfd_path, "execveat.symlink", 0);
	/*   absolute path */
	fail += check_execveat(AT_FDCWD, fullname_symlink, 0);
	/*   fd + no path, even with AT_SYMLINK_NOFOLLOW (already followed) */
	fail += check_execveat(fd_symlink, "", AT_EMPTY_PATH);
	fail += check_execveat(fd_symlink, "",
			       AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW);

	/* Symlink fails when AT_SYMLINK_NOFOLLOW set: */
	/*   dfd + path */
	fail += check_execveat_fail(dot_dfd, "execveat.symlink",
				    AT_SYMLINK_NOFOLLOW, ELOOP);
	fail += check_execveat_fail(dot_dfd_path, "execveat.symlink",
				    AT_SYMLINK_NOFOLLOW, ELOOP);
	/*   absolute path */
	fail += check_execveat_fail(AT_FDCWD, fullname_symlink,
				    AT_SYMLINK_NOFOLLOW, ELOOP);

	/* Shell script wrapping executable file: */
	/*   dfd + path */
	fail += check_execveat(subdir_dfd, "../script", 0);
	fail += check_execveat(dot_dfd, "script", 0);
	fail += check_execveat(dot_dfd_path, "script", 0);
	/*   absolute path */
	fail += check_execveat(AT_FDCWD, fullname_script, 0);
	/*   fd + no path */
	fail += check_execveat(fd_script, "", AT_EMPTY_PATH);
	fail += check_execveat(fd_script, "",
			       AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW);
	/*   O_CLOEXEC fd fails for a script (as script file inaccessible) */
	fail += check_execveat_fail(fd_script_cloexec, "", AT_EMPTY_PATH,
				    ENOENT);
	fail += check_execveat_fail(dot_dfd_cloexec, "script", 0, ENOENT);

	/* Mess with script file that's already open: */
	/*   fd + no path to a file that's been renamed */
	rename("script.ephemeral", "script.moved");
	fail += check_execveat(fd_script_ephemeral, "", AT_EMPTY_PATH);
	/*   fd + no path to a file that's been deleted */
	unlink("script.moved"); /* remove the file while fd open */
	fail += check_execveat(fd_script_ephemeral, "", AT_EMPTY_PATH);

	/* Rename a subdirectory in the path: */
	rename("subdir.ephemeral", "subdir.moved");
	fail += check_execveat(subdir_dfd_ephemeral, "../script", 0);
	fail += check_execveat(subdir_dfd_ephemeral, "script", 0);
	/* Remove the subdir and its contents */
	unlink("subdir.moved/script");
	unlink("subdir.moved");
	/* Shell loads via deleted subdir OK because name starts with .. */
	fail += check_execveat(subdir_dfd_ephemeral, "../script", 0);
	fail += check_execveat_fail(subdir_dfd_ephemeral, "script", 0, ENOENT);

	/* Flag values other than AT_SYMLINK_NOFOLLOW => EINVAL */
	fail += check_execveat_fail(dot_dfd, "execveat", 0xFFFF, EINVAL);
	/* Invalid path => ENOENT */
	fail += check_execveat_fail(dot_dfd, "no-such-file", 0, ENOENT);
	fail += check_execveat_fail(dot_dfd_path, "no-such-file", 0, ENOENT);
	fail += check_execveat_fail(AT_FDCWD, "no-such-file", 0, ENOENT);
	/* Attempt to execute directory => EACCES */
	fail += check_execveat_fail(dot_dfd, "", AT_EMPTY_PATH, EACCES);
	/* Attempt to execute non-executable => EACCES */
	fail += check_execveat_fail(dot_dfd, "Makefile", 0, EACCES);
	fail += check_execveat_fail(fd_denatured, "", AT_EMPTY_PATH, EACCES);
	fail += check_execveat_fail(fd_denatured_path, "", AT_EMPTY_PATH,
				    EACCES);
	/* Attempt to execute nonsense FD => EBADF */
	fail += check_execveat_fail(99, "", AT_EMPTY_PATH, EBADF);
	fail += check_execveat_fail(99, "execveat", 0, EBADF);
	/* Attempt to execute relative to non-directory => ENOTDIR */
	fail += check_execveat_fail(fd, "execveat", 0, ENOTDIR);

	fail += check_execveat_pathmax(root_dfd, "execveat", 0);
	fail += check_execveat_pathmax(root_dfd, "script", 1);
	return fail;
}