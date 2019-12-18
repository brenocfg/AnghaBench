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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CMD_EX ; 
 int CMD_OK ; 
 int /*<<< orphan*/  add_history (char*) ; 
 int execf (char*) ; 
 int /*<<< orphan*/  exit_shell (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  init_shell (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* readline (char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int run_shell_loop(FILE *fin, FILE *fout)
{
	char *buf;

	init_shell(fin, fout);

	while ((buf = readline("> ")) != NULL) {
		int ret = execf(buf);
		if (ret == CMD_EX)
			break;
		if (ret == CMD_OK && strlen(buf) > 0)
			add_history(buf);

		free(buf);
	}

	exit_shell(fin, fout);
	return 0;
}