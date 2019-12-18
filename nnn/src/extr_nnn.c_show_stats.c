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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_LEN_MAX ; 
 int /*<<< orphan*/  DPRINTF_S (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  F_CLI ; 
 int /*<<< orphan*/  PATH_MAX ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 int create_tmp_file () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* g_buf ; 
 int /*<<< orphan*/  g_tmpfpath ; 
 char* get_output (char*,int /*<<< orphan*/ ,char*,char*,char const*,int) ; 
 int /*<<< orphan*/  pager ; 
 int /*<<< orphan*/  pipetof (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spawn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 size_t xstrlcpy (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool show_stats(const char *fpath, const struct stat *sb)
{
	int fd;
	FILE *fp;
	char *p, *begin = g_buf;
	size_t r;

	fd = create_tmp_file();
	if (fd == -1)
		return FALSE;

	r = xstrlcpy(g_buf, "stat \"", PATH_MAX);
	r += xstrlcpy(g_buf + r - 1, fpath, PATH_MAX);
	g_buf[r - 2] = '\"';
	g_buf[r - 1] = '\0';
	DPRINTF_S(g_buf);

	fp = fdopen(fd, "w");
	if (!fp) {
		close(fd);
		return FALSE;
	}

	pipetof(g_buf, fp);

	if (S_ISREG(sb->st_mode)) {
		/* Show file(1) output */
		p = get_output(g_buf, CMD_LEN_MAX, "file", "-b", fpath, FALSE);
		if (p) {
			fprintf(fp, "\n\n ");
			while (*p) {
				if (*p == ',') {
					*p = '\0';
					fprintf(fp, " %s\n", begin);
					begin = p + 1;
				}

				++p;
			}
			fprintf(fp, " %s", begin);
		}
	}

	fprintf(fp, "\n\n");
	fclose(fp);
	close(fd);

	spawn(pager, g_tmpfpath, NULL, NULL, F_CLI);
	unlink(g_tmpfpath);
	return TRUE;
}