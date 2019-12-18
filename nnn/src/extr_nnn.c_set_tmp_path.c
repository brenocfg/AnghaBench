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
typedef  scalar_t__ uchar ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TMP_LEN_MAX ; 
 int TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_tmpfpath ; 
 scalar_t__ g_tmpfplen ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ xdiraccess (char*) ; 
 scalar_t__ xstrlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_tmp_path(void)
{
	char *path;

	if (xdiraccess("/tmp"))
		g_tmpfplen = (uchar)xstrlcpy(g_tmpfpath, "/tmp", TMP_LEN_MAX);
	else {
		path = getenv("TMPDIR");
		if (path)
			g_tmpfplen = (uchar)xstrlcpy(g_tmpfpath, path, TMP_LEN_MAX);
		else {
			fprintf(stderr, "set TMPDIR\n");
			return FALSE;
		}
	}

	return TRUE;
}