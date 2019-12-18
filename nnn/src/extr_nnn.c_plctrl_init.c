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
 int /*<<< orphan*/  CMD_LEN_MAX ; 
 size_t NNN_PIPE ; 
 int /*<<< orphan*/  TRUE ; 
 int _FAILURE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/ * env_cfg ; 
 int /*<<< orphan*/  g_buf ; 
 int /*<<< orphan*/  g_pipepath ; 
 char* g_tmpfpath ; 
 int g_tmpfplen ; 
 int getpid () ; 
 scalar_t__ mkfifo (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mkpath (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool plctrl_init(void)
{
	snprintf(g_buf, CMD_LEN_MAX, "nnn-pipe.%d", getpid());
	/* g_tmpfpath is used to generate tmp file names */
	g_tmpfpath[g_tmpfplen - 1] = '\0';
	mkpath(g_tmpfpath, g_buf, g_pipepath);
	unlink(g_pipepath);
	if (mkfifo(g_pipepath, 0600) != 0)
		return _FAILURE;

	setenv(env_cfg[NNN_PIPE], g_pipepath, TRUE);

	return _SUCCESS;
}