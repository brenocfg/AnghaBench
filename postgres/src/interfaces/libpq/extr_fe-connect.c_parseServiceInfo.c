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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  serviceFile ;
typedef  int /*<<< orphan*/  homedir ;
typedef  int /*<<< orphan*/  PQconninfoOption ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int MAXPGPATH ; 
 char* SYSCONFDIR ; 
 char* conninfo_getval (int /*<<< orphan*/ *,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int parseServiceFile (char*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pqGetHomeDirectory (char*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int
parseServiceInfo(PQconninfoOption *options, PQExpBuffer errorMessage)
{
	const char *service = conninfo_getval(options, "service");
	char		serviceFile[MAXPGPATH];
	char	   *env;
	bool		group_found = false;
	int			status;
	struct stat stat_buf;

	/*
	 * We have to special-case the environment variable PGSERVICE here, since
	 * this is and should be called before inserting environment defaults for
	 * other connection options.
	 */
	if (service == NULL)
		service = getenv("PGSERVICE");

	/* If no service name given, nothing to do */
	if (service == NULL)
		return 0;

	/*
	 * Try PGSERVICEFILE if specified, else try ~/.pg_service.conf (if that
	 * exists).
	 */
	if ((env = getenv("PGSERVICEFILE")) != NULL)
		strlcpy(serviceFile, env, sizeof(serviceFile));
	else
	{
		char		homedir[MAXPGPATH];

		if (!pqGetHomeDirectory(homedir, sizeof(homedir)))
			goto next_file;
		snprintf(serviceFile, MAXPGPATH, "%s/%s", homedir, ".pg_service.conf");
		if (stat(serviceFile, &stat_buf) != 0)
			goto next_file;
	}

	status = parseServiceFile(serviceFile, service, options, errorMessage, &group_found);
	if (group_found || status != 0)
		return status;

next_file:

	/*
	 * This could be used by any application so we can't use the binary
	 * location to find our config files.
	 */
	snprintf(serviceFile, MAXPGPATH, "%s/pg_service.conf",
			 getenv("PGSYSCONFDIR") ? getenv("PGSYSCONFDIR") : SYSCONFDIR);
	if (stat(serviceFile, &stat_buf) != 0)
		goto last_file;

	status = parseServiceFile(serviceFile, service, options, errorMessage, &group_found);
	if (status != 0)
		return status;

last_file:
	if (!group_found)
	{
		printfPQExpBuffer(errorMessage,
						  libpq_gettext("definition of service \"%s\" not found\n"), service);
		return 3;
	}

	return 0;
}