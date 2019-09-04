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
struct TYPE_2__ {char* mac_start; char* mac_end; int /*<<< orphan*/  mac_name; } ;

/* Variables and functions */
 int EOF ; 
 int code ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char getchar () ; 
 int /*<<< orphan*/  gets (int /*<<< orphan*/ *) ; 
 scalar_t__ interactive ; 
 int /*<<< orphan*/ * line ; 
 char* macbuf ; 
 int macnum ; 
 TYPE_1__* macros ; 
 int /*<<< orphan*/  makeargv () ; 
 int margc ; 
 char** margv ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

void macdef(int argc, const char *argv[])
{
	char *tmp;
	int c;

	if (macnum == 16) {
		printf("Limit of 16 macros have already been defined\n");
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if (argc < 2) {
		(void) strcat(line, " ");
		printf("(macro name) ");
		(void) fflush(stdout);
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc != 2) {
		printf("Usage: %s macro_name\n",argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if (interactive) {
		printf("Enter macro line by line, terminating it with a null line\n");
		(void) fflush(stdout);
	}
	(void) strncpy(macros[macnum].mac_name, argv[1], 8);
	if (macnum == 0) {
		macros[macnum].mac_start = macbuf;
	}
	else {
		macros[macnum].mac_start = macros[macnum - 1].mac_end + 1;
	}
	tmp = macros[macnum].mac_start;
	while (tmp != macbuf+4096) {
		if ((c = getchar()) == EOF) {
			printf("macdef:end of file encountered\n");
			(void) fflush(stdout);
			code = -1;
			return;
		}
		if ((*tmp = c) == '\n') {
			if (tmp == macros[macnum].mac_start) {
				macros[macnum++].mac_end = tmp;
				code = 0;
				return;
			}
			if (*(tmp-1) == '\0') {
				macros[macnum++].mac_end = tmp - 1;
				code = 0;
				return;
			}
			*tmp = '\0';
		}
		tmp++;
	}
	while (1) {
		while ((c = getchar()) != '\n' && c != EOF)
			/* LOOP */;
		if (c == EOF || getchar() == '\n') {
			printf("Macro not defined - 4k buffer exceeded\n");
			(void) fflush(stdout);
			code = -1;
			return;
		}
	}
}