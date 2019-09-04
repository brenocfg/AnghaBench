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
typedef  int /*<<< orphan*/  cwd ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  errno ; 
 char* getcwd (char*,int) ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mount (char*,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chdir_to_tmpfs(void)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != cwd)
		ksft_exit_fail_msg("getcwd - %s\n", strerror(errno));

	if (mount("private_tmp", ".", "tmpfs", 0, "mode=0777") != 0)
		ksft_exit_fail_msg("mount private tmpfs - %s\n",
					strerror(errno));

	if (chdir(cwd) != 0)
		ksft_exit_fail_msg("chdir to private tmpfs - %s\n",
					strerror(errno));
}