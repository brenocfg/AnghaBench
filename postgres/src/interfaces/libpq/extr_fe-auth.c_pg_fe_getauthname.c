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
typedef  int /*<<< orphan*/  username ;
typedef  scalar_t__ uid_t ;
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  pwdbuf ;
typedef  scalar_t__ PQExpBuffer ;
typedef  int DWORD ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetUserName (char*,int*) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  pglock_thread () ; 
 int /*<<< orphan*/  pgunlock_thread () ; 
 int pqGetpwuid (scalar_t__,struct passwd*,char*,int,struct passwd**) ; 
 int /*<<< orphan*/  printfPQExpBuffer (scalar_t__,int /*<<< orphan*/ ,...) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strerror_r (int,char*,int) ; 

char *
pg_fe_getauthname(PQExpBuffer errorMessage)
{
	char	   *result = NULL;
	const char *name = NULL;

#ifdef WIN32
	/* Microsoft recommends buffer size of UNLEN+1, where UNLEN = 256 */
	char		username[256 + 1];
	DWORD		namesize = sizeof(username);
#else
	uid_t		user_id = geteuid();
	char		pwdbuf[BUFSIZ];
	struct passwd pwdstr;
	struct passwd *pw = NULL;
	int			pwerr;
#endif

	/*
	 * Some users are using configure --enable-thread-safety-force, so we
	 * might as well do the locking within our library to protect
	 * pqGetpwuid(). In fact, application developers can use getpwuid() in
	 * their application if they use the locking call we provide, or install
	 * their own locking function using PQregisterThreadLock().
	 */
	pglock_thread();

#ifdef WIN32
	if (GetUserName(username, &namesize))
		name = username;
	else if (errorMessage)
		printfPQExpBuffer(errorMessage,
						  libpq_gettext("user name lookup failure: error code %lu\n"),
						  GetLastError());
#else
	pwerr = pqGetpwuid(user_id, &pwdstr, pwdbuf, sizeof(pwdbuf), &pw);
	if (pw != NULL)
		name = pw->pw_name;
	else if (errorMessage)
	{
		if (pwerr != 0)
			printfPQExpBuffer(errorMessage,
							  libpq_gettext("could not look up local user ID %d: %s\n"),
							  (int) user_id,
							  strerror_r(pwerr, pwdbuf, sizeof(pwdbuf)));
		else
			printfPQExpBuffer(errorMessage,
							  libpq_gettext("local user with ID %d does not exist\n"),
							  (int) user_id);
	}
#endif

	if (name)
	{
		result = strdup(name);
		if (result == NULL && errorMessage)
			printfPQExpBuffer(errorMessage,
							  libpq_gettext("out of memory\n"));
	}

	pgunlock_thread();

	return result;
}