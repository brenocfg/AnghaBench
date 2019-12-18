#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* hostaddr; char* host; char* port; int /*<<< orphan*/  password; void* type; } ;
typedef  TYPE_1__ pg_conn_host ;
typedef  int /*<<< orphan*/  homedir ;
struct TYPE_5__ {char* pghostaddr; int nconnhost; char* pghost; char* pgport; char* pguser; char* dbName; char* pgpass; char* pgpassfile; char* channel_binding; char* sslmode; char* gssencmode; char* client_encoding_initial; char* target_session_attrs; int options_valid; int /*<<< orphan*/  errorMessage; void* status; TYPE_1__* connhost; scalar_t__ whichhost; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 void* CHT_HOST_ADDRESS ; 
 void* CHT_HOST_NAME ; 
 void* CHT_UNIX_SOCKET ; 
 void* CONNECTION_BAD ; 
 char* DEFAULT_PGSOCKET_DIR ; 
 char* DefaultChannelBinding ; 
 char* DefaultGSSMode ; 
 char* DefaultHost ; 
 char* DefaultSSLMode ; 
 int MAXPGPATH ; 
 char* PGPASSFILE ; 
 scalar_t__ calloc (int,int) ; 
 void* count_comma_separated_elems (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_absolute_path (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 char* malloc (int) ; 
 void* parse_comma_separated_list (char**,int*) ; 
 int /*<<< orphan*/  passwordFromFile (char const*,char*,char*,char*,char*) ; 
 char* pg_encoding_to_char (int /*<<< orphan*/ ) ; 
 char* pg_fe_getauthname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_get_encoding_from_locale (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pqGetHomeDirectory (char*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strdup (char*) ; 

__attribute__((used)) static bool
connectOptions2(PGconn *conn)
{
	int			i;

	/*
	 * Allocate memory for details about each host to which we might possibly
	 * try to connect.  For that, count the number of elements in the hostaddr
	 * or host options.  If neither is given, assume one host.
	 */
	conn->whichhost = 0;
	if (conn->pghostaddr && conn->pghostaddr[0] != '\0')
		conn->nconnhost = count_comma_separated_elems(conn->pghostaddr);
	else if (conn->pghost && conn->pghost[0] != '\0')
		conn->nconnhost = count_comma_separated_elems(conn->pghost);
	else
		conn->nconnhost = 1;
	conn->connhost = (pg_conn_host *)
		calloc(conn->nconnhost, sizeof(pg_conn_host));
	if (conn->connhost == NULL)
		goto oom_error;

	/*
	 * We now have one pg_conn_host structure per possible host.  Fill in the
	 * host and hostaddr fields for each, by splitting the parameter strings.
	 */
	if (conn->pghostaddr != NULL && conn->pghostaddr[0] != '\0')
	{
		char	   *s = conn->pghostaddr;
		bool		more = true;

		for (i = 0; i < conn->nconnhost && more; i++)
		{
			conn->connhost[i].hostaddr = parse_comma_separated_list(&s, &more);
			if (conn->connhost[i].hostaddr == NULL)
				goto oom_error;
		}

		/*
		 * If hostaddr was given, the array was allocated according to the
		 * number of elements in the hostaddr list, so it really should be the
		 * right size.
		 */
		Assert(!more);
		Assert(i == conn->nconnhost);
	}

	if (conn->pghost != NULL && conn->pghost[0] != '\0')
	{
		char	   *s = conn->pghost;
		bool		more = true;

		for (i = 0; i < conn->nconnhost && more; i++)
		{
			conn->connhost[i].host = parse_comma_separated_list(&s, &more);
			if (conn->connhost[i].host == NULL)
				goto oom_error;
		}

		/* Check for wrong number of host items. */
		if (more || i != conn->nconnhost)
		{
			conn->status = CONNECTION_BAD;
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("could not match %d host names to %d hostaddr values\n"),
							  count_comma_separated_elems(conn->pghost), conn->nconnhost);
			return false;
		}
	}

	/*
	 * Now, for each host slot, identify the type of address spec, and fill in
	 * the default address if nothing was given.
	 */
	for (i = 0; i < conn->nconnhost; i++)
	{
		pg_conn_host *ch = &conn->connhost[i];

		if (ch->hostaddr != NULL && ch->hostaddr[0] != '\0')
			ch->type = CHT_HOST_ADDRESS;
		else if (ch->host != NULL && ch->host[0] != '\0')
		{
			ch->type = CHT_HOST_NAME;
#ifdef HAVE_UNIX_SOCKETS
			if (is_absolute_path(ch->host))
				ch->type = CHT_UNIX_SOCKET;
#endif
		}
		else
		{
			if (ch->host)
				free(ch->host);
#ifdef HAVE_UNIX_SOCKETS
			ch->host = strdup(DEFAULT_PGSOCKET_DIR);
			ch->type = CHT_UNIX_SOCKET;
#else
			ch->host = strdup(DefaultHost);
			ch->type = CHT_HOST_NAME;
#endif
			if (ch->host == NULL)
				goto oom_error;
		}
	}

	/*
	 * Next, work out the port number corresponding to each host name.
	 *
	 * Note: unlike the above for host names, this could leave the port fields
	 * as null or empty strings.  We will substitute DEF_PGPORT whenever we
	 * read such a port field.
	 */
	if (conn->pgport != NULL && conn->pgport[0] != '\0')
	{
		char	   *s = conn->pgport;
		bool		more = true;

		for (i = 0; i < conn->nconnhost && more; i++)
		{
			conn->connhost[i].port = parse_comma_separated_list(&s, &more);
			if (conn->connhost[i].port == NULL)
				goto oom_error;
		}

		/*
		 * If exactly one port was given, use it for every host.  Otherwise,
		 * there must be exactly as many ports as there were hosts.
		 */
		if (i == 1 && !more)
		{
			for (i = 1; i < conn->nconnhost; i++)
			{
				conn->connhost[i].port = strdup(conn->connhost[0].port);
				if (conn->connhost[i].port == NULL)
					goto oom_error;
			}
		}
		else if (more || i != conn->nconnhost)
		{
			conn->status = CONNECTION_BAD;
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("could not match %d port numbers to %d hosts\n"),
							  count_comma_separated_elems(conn->pgport), conn->nconnhost);
			return false;
		}
	}

	/*
	 * If user name was not given, fetch it.  (Most likely, the fetch will
	 * fail, since the only way we get here is if pg_fe_getauthname() failed
	 * during conninfo_add_defaults().  But now we want an error message.)
	 */
	if (conn->pguser == NULL || conn->pguser[0] == '\0')
	{
		if (conn->pguser)
			free(conn->pguser);
		conn->pguser = pg_fe_getauthname(&conn->errorMessage);
		if (!conn->pguser)
		{
			conn->status = CONNECTION_BAD;
			return false;
		}
	}

	/*
	 * If database name was not given, default it to equal user name
	 */
	if (conn->dbName == NULL || conn->dbName[0] == '\0')
	{
		if (conn->dbName)
			free(conn->dbName);
		conn->dbName = strdup(conn->pguser);
		if (!conn->dbName)
			goto oom_error;
	}

	/*
	 * If password was not given, try to look it up in password file.  Note
	 * that the result might be different for each host/port pair.
	 */
	if (conn->pgpass == NULL || conn->pgpass[0] == '\0')
	{
		/* If password file wasn't specified, use ~/PGPASSFILE */
		if (conn->pgpassfile == NULL || conn->pgpassfile[0] == '\0')
		{
			char		homedir[MAXPGPATH];

			if (pqGetHomeDirectory(homedir, sizeof(homedir)))
			{
				if (conn->pgpassfile)
					free(conn->pgpassfile);
				conn->pgpassfile = malloc(MAXPGPATH);
				if (!conn->pgpassfile)
					goto oom_error;
				snprintf(conn->pgpassfile, MAXPGPATH, "%s/%s",
						 homedir, PGPASSFILE);
			}
		}

		if (conn->pgpassfile != NULL && conn->pgpassfile[0] != '\0')
		{
			for (i = 0; i < conn->nconnhost; i++)
			{
				/*
				 * Try to get a password for this host from file.  We use host
				 * for the hostname search key if given, else hostaddr (at
				 * least one of them is guaranteed nonempty by now).
				 */
				const char *pwhost = conn->connhost[i].host;

				if (pwhost == NULL || pwhost[0] == '\0')
					pwhost = conn->connhost[i].hostaddr;

				conn->connhost[i].password =
					passwordFromFile(pwhost,
									 conn->connhost[i].port,
									 conn->dbName,
									 conn->pguser,
									 conn->pgpassfile);
			}
		}
	}

	/*
	 * validate channel_binding option
	 */
	if (conn->channel_binding)
	{
		if (strcmp(conn->channel_binding, "disable") != 0
			&& strcmp(conn->channel_binding, "prefer") != 0
			&& strcmp(conn->channel_binding, "require") != 0)
		{
			conn->status = CONNECTION_BAD;
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("invalid channel_binding value: \"%s\"\n"),
							  conn->channel_binding);
			return false;
		}
	}
	else
	{
		conn->channel_binding = strdup(DefaultChannelBinding);
		if (!conn->channel_binding)
			goto oom_error;
	}

	/*
	 * validate sslmode option
	 */
	if (conn->sslmode)
	{
		if (strcmp(conn->sslmode, "disable") != 0
			&& strcmp(conn->sslmode, "allow") != 0
			&& strcmp(conn->sslmode, "prefer") != 0
			&& strcmp(conn->sslmode, "require") != 0
			&& strcmp(conn->sslmode, "verify-ca") != 0
			&& strcmp(conn->sslmode, "verify-full") != 0)
		{
			conn->status = CONNECTION_BAD;
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("invalid sslmode value: \"%s\"\n"),
							  conn->sslmode);
			return false;
		}

#ifndef USE_SSL
		switch (conn->sslmode[0])
		{
			case 'a':			/* "allow" */
			case 'p':			/* "prefer" */

				/*
				 * warn user that an SSL connection will never be negotiated
				 * since SSL was not compiled in?
				 */
				break;

			case 'r':			/* "require" */
			case 'v':			/* "verify-ca" or "verify-full" */
				conn->status = CONNECTION_BAD;
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("sslmode value \"%s\" invalid when SSL support is not compiled in\n"),
								  conn->sslmode);
				return false;
		}
#endif
	}
	else
	{
		conn->sslmode = strdup(DefaultSSLMode);
		if (!conn->sslmode)
			goto oom_error;
	}

	/*
	 * validate gssencmode option
	 */
	if (conn->gssencmode)
	{
		if (strcmp(conn->gssencmode, "disable") != 0 &&
			strcmp(conn->gssencmode, "prefer") != 0 &&
			strcmp(conn->gssencmode, "require") != 0)
		{
			conn->status = CONNECTION_BAD;
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("invalid gssencmode value: \"%s\"\n"),
							  conn->gssencmode);
			return false;
		}
#ifndef ENABLE_GSS
		if (strcmp(conn->gssencmode, "require") == 0)
		{
			conn->status = CONNECTION_BAD;
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("gssencmode value \"%s\" invalid when GSSAPI support is not compiled in\n"),
							  conn->gssencmode);
			return false;
		}
#endif
	}
	else
	{
		conn->gssencmode = strdup(DefaultGSSMode);
		if (!conn->gssencmode)
			goto oom_error;
	}

	/*
	 * Resolve special "auto" client_encoding from the locale
	 */
	if (conn->client_encoding_initial &&
		strcmp(conn->client_encoding_initial, "auto") == 0)
	{
		free(conn->client_encoding_initial);
		conn->client_encoding_initial = strdup(pg_encoding_to_char(pg_get_encoding_from_locale(NULL, true)));
		if (!conn->client_encoding_initial)
			goto oom_error;
	}

	/*
	 * Validate target_session_attrs option.
	 */
	if (conn->target_session_attrs)
	{
		if (strcmp(conn->target_session_attrs, "any") != 0
			&& strcmp(conn->target_session_attrs, "read-write") != 0)
		{
			conn->status = CONNECTION_BAD;
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("invalid target_session_attrs value: \"%s\"\n"),
							  conn->target_session_attrs);
			return false;
		}
	}

	/*
	 * Only if we get this far is it appropriate to try to connect. (We need a
	 * state flag, rather than just the boolean result of this function, in
	 * case someone tries to PQreset() the PGconn.)
	 */
	conn->options_valid = true;

	return true;

oom_error:
	conn->status = CONNECTION_BAD;
	printfPQExpBuffer(&conn->errorMessage,
					  libpq_gettext("out of memory\n"));
	return false;
}