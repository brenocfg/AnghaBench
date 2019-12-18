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
typedef  int /*<<< orphan*/  sverbuf ;
typedef  int /*<<< orphan*/  cverbuf ;
struct TYPE_2__ {int sversion; char* progname; int /*<<< orphan*/  db; int /*<<< orphan*/  notty; int /*<<< orphan*/  quiet; } ;

/* Variables and functions */
 char* PG_VERSION ; 
 int PG_VERSION_NUM ; 
 char* PQparameterStatus (int /*<<< orphan*/ ,char*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  checkWin32Codepage () ; 
 char* formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  printGSSInfo () ; 
 int /*<<< orphan*/  printSSLInfo () ; 
 int /*<<< orphan*/  printf (char*,char*,char*,...) ; 
 TYPE_1__ pset ; 

void
connection_warnings(bool in_startup)
{
	if (!pset.quiet && !pset.notty)
	{
		int			client_ver = PG_VERSION_NUM;
		char		cverbuf[32];
		char		sverbuf[32];

		if (pset.sversion != client_ver)
		{
			const char *server_version;

			/* Try to get full text form, might include "devel" etc */
			server_version = PQparameterStatus(pset.db, "server_version");
			/* Otherwise fall back on pset.sversion */
			if (!server_version)
			{
				formatPGVersionNumber(pset.sversion, true,
									  sverbuf, sizeof(sverbuf));
				server_version = sverbuf;
			}

			printf(_("%s (%s, server %s)\n"),
				   pset.progname, PG_VERSION, server_version);
		}
		/* For version match, only print psql banner on startup. */
		else if (in_startup)
			printf("%s (%s)\n", pset.progname, PG_VERSION);

		if (pset.sversion / 100 > client_ver / 100)
			printf(_("WARNING: %s major version %s, server major version %s.\n"
					 "         Some psql features might not work.\n"),
				   pset.progname,
				   formatPGVersionNumber(client_ver, false,
										 cverbuf, sizeof(cverbuf)),
				   formatPGVersionNumber(pset.sversion, false,
										 sverbuf, sizeof(sverbuf)));

#ifdef WIN32
		if (in_startup)
			checkWin32Codepage();
#endif
		printSSLInfo();
		printGSSInfo();
	}
}