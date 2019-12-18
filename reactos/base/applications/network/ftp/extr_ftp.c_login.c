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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_2__ {int /*<<< orphan*/  mac_name; } ;

/* Variables and functions */
 int COMPLETE ; 
 int CONTINUE ; 
 int code ; 
 int command (char*,char const*) ; 
 int /*<<< orphan*/  domacro (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* getpass (char*) ; 
 int /*<<< orphan*/  line ; 
 int macnum ; 
 TYPE_1__* macros ; 
 int /*<<< orphan*/  makeargv () ; 
 int /*<<< orphan*/  margc ; 
 int /*<<< orphan*/  margv ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 scalar_t__ proxy ; 
 int ruserpass (char const*,char**,char**,char**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

int login(const char *host)
{
	char tmp[80];
	char *puser, *ppass, *pacct;
	const char *user, *pass, *acct;
	int n, aflag = 0;

	user = pass = acct = 0;
	n = ruserpass(host, &puser, &ppass, &pacct);
	if (n < 0) {
		code = -1;
		return(0);
	}
	if (0 != n) {
		user = puser;
		pass = ppass;
		acct = pacct;
	}
	while (user == NULL) {
		const char *myname = "none"; // This needs to become the username env

		if (myname)
			printf("Name (%s:%s): ", host, myname);
		else
			printf("Name (%s): ", host);
		(void) fflush(stdout);
		(void) fgets(tmp, sizeof(tmp) - 1, stdin);
		tmp[strlen(tmp) - 1] = '\0';
		if (*tmp == '\0')
			user = myname;
		else
			user = tmp;
	}
	n = command("USER %s", user);
	if (n == CONTINUE) {
		if (pass == NULL)
			pass = getpass("Password:");
		n = command("PASS %s", pass);
		fflush(stdin);
	}
	if (n == CONTINUE) {
		aflag++;
		acct = getpass("Account:");
		n = command("ACCT %s", acct);
	}
	if (n != COMPLETE) {
		fprintf(stderr, "Login failed.\n");
		return (0);
	}
	if (!aflag && acct != NULL)
		(void) command("ACCT %s", acct);
	if (proxy)
		return(1);
	for (n = 0; n < macnum; ++n) {
		if (!strcmp("init", macros[n].mac_name)) {
			(void) strcpy(line, "$init");
			makeargv();
			domacro(margc, margv);
			break;
		}
	}
	return (1);
}