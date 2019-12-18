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
 int /*<<< orphan*/  add_history (char*) ; 
 int chdir (char*) ; 
 int /*<<< orphan*/  exitcurses () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* g_buf ; 
 int /*<<< orphan*/  printwarn (int*) ; 
 char* readline (char*) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *getreadline(char *prompt, char *path, char *curpath, int *presel)
{
	/* Switch to current path for readline(3) */
	if (chdir(path) == -1) {
		printwarn(presel);
		return NULL;
	}

	exitcurses();

	char *input = readline(prompt);

	refresh();

	if (chdir(curpath) == -1) {
		printwarn(presel);
		free(input);
		return NULL;
	}

	if (input && input[0]) {
		add_history(input);
		xstrlcpy(g_buf, input, CMD_LEN_MAX);
		free(input);
		return g_buf;
	}

	free(input);
	return NULL;
}