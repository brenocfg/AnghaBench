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
 int /*<<< orphan*/  AT_EMPTY_PATH ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int XX_DIR_LEN ; 
 scalar_t__ check_execveat (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_execveat_invoked_rc (int,char*,int /*<<< orphan*/ ,int,int) ; 
 int errno ; 
 int /*<<< orphan*/  exe_cp (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* longpath ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strerror (int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int check_execveat_pathmax(int root_dfd, const char *src, int is_script)
{
	int fail = 0;
	int ii, count, len;
	char longname[XX_DIR_LEN + 1];
	int fd;

	if (*longpath == '\0') {
		/* Create a filename close to PATH_MAX in length */
		char *cwd = getcwd(NULL, 0);

		if (!cwd) {
			printf("Failed to getcwd(), errno=%d (%s)\n",
			       errno, strerror(errno));
			return 2;
		}
		strcpy(longpath, cwd);
		strcat(longpath, "/");
		memset(longname, 'x', XX_DIR_LEN - 1);
		longname[XX_DIR_LEN - 1] = '/';
		longname[XX_DIR_LEN] = '\0';
		count = (PATH_MAX - 3 - strlen(cwd)) / XX_DIR_LEN;
		for (ii = 0; ii < count; ii++) {
			strcat(longpath, longname);
			mkdir(longpath, 0755);
		}
		len = (PATH_MAX - 3 - strlen(cwd)) - (count * XX_DIR_LEN);
		if (len <= 0)
			len = 1;
		memset(longname, 'y', len);
		longname[len] = '\0';
		strcat(longpath, longname);
		free(cwd);
	}
	exe_cp(src, longpath);

	/*
	 * Execute as a pre-opened file descriptor, which works whether this is
	 * a script or not (because the interpreter sees a filename like
	 * "/dev/fd/20").
	 */
	fd = open(longpath, O_RDONLY);
	if (fd > 0) {
		printf("Invoke copy of '%s' via filename of length %zu:\n",
			src, strlen(longpath));
		fail += check_execveat(fd, "", AT_EMPTY_PATH);
	} else {
		printf("Failed to open length %zu filename, errno=%d (%s)\n",
			strlen(longpath), errno, strerror(errno));
		fail++;
	}

	/*
	 * Execute as a long pathname relative to "/".  If this is a script,
	 * the interpreter will launch but fail to open the script because its
	 * name ("/dev/fd/5/xxx....") is bigger than PATH_MAX.
	 *
	 * The failure code is usually 127 (POSIX: "If a command is not found,
	 * the exit status shall be 127."), but some systems give 126 (POSIX:
	 * "If the command name is found, but it is not an executable utility,
	 * the exit status shall be 126."), so allow either.
	 */
	if (is_script)
		fail += check_execveat_invoked_rc(root_dfd, longpath + 1, 0,
						  127, 126);
	else
		fail += check_execveat(root_dfd, longpath + 1, 0);

	return fail;
}