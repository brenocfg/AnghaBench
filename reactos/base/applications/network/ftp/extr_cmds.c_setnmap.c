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
 scalar_t__ MAXPATHLEN ; 
 char* altarg ; 
 int code ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gets (int /*<<< orphan*/ *) ; 
 char* index (char*,char) ; 
 int /*<<< orphan*/ * line ; 
 int /*<<< orphan*/  makeargv () ; 
 int mapflag ; 
 int /*<<< orphan*/  mapin ; 
 int /*<<< orphan*/  mapout ; 
 int margc ; 
 char** margv ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ proxy ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void setnmap(int argc, const char *argv[])
{
	char *cp;

	if (argc == 1) {
		mapflag = 0;
		printf("Nmap off.\n");
		(void) fflush(stdout);
		code = mapflag;
		return;
	}
	if (argc < 3) {
		(void) strcat(line, " ");
		printf("(mapout) ");
		(void) fflush(stdout);
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 3) {
		printf("Usage: %s [mapin mapout]\n",argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	mapflag = 1;
	code = 1;
	cp = index(altarg, ' ');
	if (proxy) {
		while(*++cp == ' ');
		altarg = cp;
		cp = index(altarg, ' ');
	}
	*cp = '\0';
	(void) strncpy(mapin, altarg, MAXPATHLEN - 1);
	while (*++cp == ' ');
	(void) strncpy(mapout, cp, MAXPATHLEN - 1);
}