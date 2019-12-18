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
typedef  int uint ;
typedef  int /*<<< orphan*/  renamecmd ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF_S (char*) ; 
 int /*<<< orphan*/  DPRINTF_U (int) ; 
 int FALSE ; 
 int /*<<< orphan*/  F_CLI ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 size_t SH_EXEC ; 
 int TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 char* cp ; 
 int create_tmp_file () ; 
 int /*<<< orphan*/  editor ; 
 char* g_selpath ; 
 char* g_tmpfpath ; 
 int lines_in_file (int,char*,int) ; 
 char* mv ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selbufpos ; 
 int /*<<< orphan*/  seltofile (int,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,char const*,...) ; 
 int /*<<< orphan*/  spawn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * utils ; 

__attribute__((used)) static bool cpmv_rename(int choice, const char *path)
{
	int fd;
	uint count = 0, lines = 0;
	bool ret = FALSE;
	char *cmd = (choice == 'c' ? cp : mv);
	static const char formatcmd[] = "sed -i 's|^\\(\\(.*/\\)\\(.*\\)$\\)|#\\1\\n\\3|' %s";
	static const char renamecmd[] = "sed 's|^\\([^#][^/]\\?.*\\)$|%s/\\1|;s|^#\\(/.*\\)$|\\1|' %s | tr '\\n' '\\0' | xargs -0 -o -n2 %s";
	char buf[sizeof(renamecmd) + sizeof(cmd) + (PATH_MAX << 1)];

	fd = create_tmp_file();
	if (fd == -1)
		return ret;

	/* selsafe() returned TRUE for this to be called */
	if (!selbufpos) {
		snprintf(buf, sizeof(buf), "cat %s | tr '\\0' '\\n' > %s", g_selpath, g_tmpfpath);
		spawn(utils[SH_EXEC], buf, NULL, NULL, F_CLI);

		count = lines_in_file(fd, buf, sizeof(buf));
		if (!count)
			goto finish;
	} else
		seltofile(fd, &count);

	close(fd);

	snprintf(buf, sizeof(buf), formatcmd, g_tmpfpath);
	spawn(utils[SH_EXEC], buf, NULL, path, F_CLI);

	spawn(editor, g_tmpfpath, NULL, path, F_CLI);

	fd = open(g_tmpfpath, O_RDONLY);
	if (fd == -1)
		goto finish;

	lines = lines_in_file(fd, buf, sizeof(buf));
	DPRINTF_U(count);
	DPRINTF_U(lines);
	if (!lines || (2 * count != lines)) {
		DPRINTF_S("num mismatch");
		goto finish;
	}

	snprintf(buf, sizeof(buf), renamecmd, path, g_tmpfpath, cmd);
	spawn(utils[SH_EXEC], buf, NULL, path, F_CLI);
	ret = TRUE;

finish:
	if (fd >= 0)
		close(fd);

	return ret;
}