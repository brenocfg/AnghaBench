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
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  exec_failed (char const*) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void exec_man_cmd(const char *cmd, const char *page)
{
	char *shell_cmd;

	if (asprintf(&shell_cmd, "%s %s", cmd, page) > 0) {
		execl("/bin/sh", "sh", "-c", shell_cmd, NULL);
		free(shell_cmd);
	}
	exec_failed(cmd);
}