#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  exec_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  free (char const**) ; 
 char** prepare_exec_cmd (char const**) ; 
 TYPE_1__ subcmd_config ; 

int execv_cmd(const char **argv) {
	const char **nargv = prepare_exec_cmd(argv);

	/* execvp() can only ever return if it fails */
	execvp(subcmd_config.exec_name, (char **)nargv);

	free(nargv);
	return -1;
}