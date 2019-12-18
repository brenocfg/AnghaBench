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
 char* ap ; 
 int /*<<< orphan*/  command (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void account(int argc, const char *argv[])
{
	char acct[50], *getpass(), *ap;

	if (argc > 1) {
		++argv;
		--argc;
		(void) strncpy(acct,*argv,49);
		acct[49] = '\0';
		while (argc > 1) {
			--argc;
			++argv;
			(void) strncat(acct,*argv, 49-strlen(acct));
		}
		ap = acct;
	}
	else {
		ap = getpass("Account:");
	}
	(void) command("ACCT %s", ap);
}