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
 int /*<<< orphan*/  NOCATGETS (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workshop_toolbar_button (char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void
process_toolbarButton(
	char	*cmd)			/* button definition */
{
	char *label  = strtok(&cmd[14], NOCATGETS("\001"));
	char *verb  = strtok(NULL, NOCATGETS("\001"));
	char *senseVerb  = strtok(NULL, NOCATGETS("\001"));
	char *filepos  = strtok(NULL, NOCATGETS("\001"));
	char *help  = strtok(NULL, NOCATGETS("\001"));
	char *sense  = strtok(NULL, NOCATGETS("\001"));
	char *file  = strtok(NULL, NOCATGETS("\001"));
	char *left  = strtok(NULL, NOCATGETS("\n"));

	if (!strcmp(label, NOCATGETS("-"))) {
		label = NULL;
	}
	if (!strcmp(help, NOCATGETS("-"))) {
		help = NULL;
	}
	if (!strcmp(file, NOCATGETS("-"))) {
		file = NULL;
	}
	if (!strcmp(senseVerb, NOCATGETS("-"))) {
		senseVerb = NULL;
	}
	workshop_toolbar_button(label, verb, senseVerb, filepos, help,
				sense, file, left);
}