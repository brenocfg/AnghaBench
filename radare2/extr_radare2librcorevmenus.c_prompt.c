#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {TYPE_1__* line; } ;
struct TYPE_3__ {char* prompt; char* contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ r_cons_fgets (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_show_cursor (int) ; 
 TYPE_2__* r_cons_singleton () ; 
 int /*<<< orphan*/  r_line_set_prompt (char const*) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static char *prompt(const char *str, const char *txt) {
	char cmd[1024];
	char *res = NULL;
	char *oprompt = strdup (r_cons_singleton ()->line->prompt);
	r_cons_show_cursor (true);
	if (txt && *txt) {
		free (r_cons_singleton ()->line->contents);
		r_cons_singleton ()->line->contents = strdup (txt);
	} else {
		R_FREE (r_cons_singleton ()->line->contents);
	}
	*cmd = '\0';
	r_line_set_prompt (str);
	if (r_cons_fgets (cmd, sizeof (cmd) - 1, 0, NULL) < 0) {
		*cmd = '\0';
	}
	//line[strlen(line)-1]='\0';
	if (*cmd) {
		res = strdup (cmd);
	}
	r_line_set_prompt (oprompt);
	free (oprompt);
	R_FREE (r_cons_singleton ()->line->contents);
	return res;
}