#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* data; } ;
typedef  int /*<<< orphan*/  PQconninfoOption ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 scalar_t__ PQExpBufferDataBroken (TYPE_1__) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  conninfo_storeval (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  conninfo_uri_parse_params (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 
 int uri_prefix_length (char const*) ; 

__attribute__((used)) static bool
conninfo_uri_parse_options(PQconninfoOption *options, const char *uri,
						   PQExpBuffer errorMessage)
{
	int			prefix_len;
	char	   *p;
	char	   *buf = NULL;
	char	   *start;
	char		prevchar = '\0';
	char	   *user = NULL;
	char	   *host = NULL;
	bool		retval = false;
	PQExpBufferData hostbuf;
	PQExpBufferData portbuf;

	initPQExpBuffer(&hostbuf);
	initPQExpBuffer(&portbuf);
	if (PQExpBufferDataBroken(hostbuf) || PQExpBufferDataBroken(portbuf))
	{
		printfPQExpBuffer(errorMessage,
						  libpq_gettext("out of memory\n"));
		goto cleanup;
	}

	/* need a modifiable copy of the input URI */
	buf = strdup(uri);
	if (buf == NULL)
	{
		printfPQExpBuffer(errorMessage,
						  libpq_gettext("out of memory\n"));
		goto cleanup;
	}
	start = buf;

	/* Skip the URI prefix */
	prefix_len = uri_prefix_length(uri);
	if (prefix_len == 0)
	{
		/* Should never happen */
		printfPQExpBuffer(errorMessage,
						  libpq_gettext("invalid URI propagated to internal parser routine: \"%s\"\n"),
						  uri);
		goto cleanup;
	}
	start += prefix_len;
	p = start;

	/* Look ahead for possible user credentials designator */
	while (*p && *p != '@' && *p != '/')
		++p;
	if (*p == '@')
	{
		/*
		 * Found username/password designator, so URI should be of the form
		 * "scheme://user[:password]@[netloc]".
		 */
		user = start;

		p = user;
		while (*p != ':' && *p != '@')
			++p;

		/* Save last char and cut off at end of user name */
		prevchar = *p;
		*p = '\0';

		if (*user &&
			!conninfo_storeval(options, "user", user,
							   errorMessage, false, true))
			goto cleanup;

		if (prevchar == ':')
		{
			const char *password = p + 1;

			while (*p != '@')
				++p;
			*p = '\0';

			if (*password &&
				!conninfo_storeval(options, "password", password,
								   errorMessage, false, true))
				goto cleanup;
		}

		/* Advance past end of parsed user name or password token */
		++p;
	}
	else
	{
		/*
		 * No username/password designator found.  Reset to start of URI.
		 */
		p = start;
	}

	/*
	 * There may be multiple netloc[:port] pairs, each separated from the next
	 * by a comma.  When we initially enter this loop, "p" has been
	 * incremented past optional URI credential information at this point and
	 * now points at the "netloc" part of the URI.  On subsequent loop
	 * iterations, "p" has been incremented past the comma separator and now
	 * points at the start of the next "netloc".
	 */
	for (;;)
	{
		/*
		 * Look for IPv6 address.
		 */
		if (*p == '[')
		{
			host = ++p;
			while (*p && *p != ']')
				++p;
			if (!*p)
			{
				printfPQExpBuffer(errorMessage,
								  libpq_gettext("end of string reached when looking for matching \"]\" in IPv6 host address in URI: \"%s\"\n"),
								  uri);
				goto cleanup;
			}
			if (p == host)
			{
				printfPQExpBuffer(errorMessage,
								  libpq_gettext("IPv6 host address may not be empty in URI: \"%s\"\n"),
								  uri);
				goto cleanup;
			}

			/* Cut off the bracket and advance */
			*(p++) = '\0';

			/*
			 * The address may be followed by a port specifier or a slash or a
			 * query or a separator comma.
			 */
			if (*p && *p != ':' && *p != '/' && *p != '?' && *p != ',')
			{
				printfPQExpBuffer(errorMessage,
								  libpq_gettext("unexpected character \"%c\" at position %d in URI (expected \":\" or \"/\"): \"%s\"\n"),
								  *p, (int) (p - buf + 1), uri);
				goto cleanup;
			}
		}
		else
		{
			/* not an IPv6 address: DNS-named or IPv4 netloc */
			host = p;

			/*
			 * Look for port specifier (colon) or end of host specifier
			 * (slash) or query (question mark) or host separator (comma).
			 */
			while (*p && *p != ':' && *p != '/' && *p != '?' && *p != ',')
				++p;
		}

		/* Save the hostname terminator before we null it */
		prevchar = *p;
		*p = '\0';

		appendPQExpBufferStr(&hostbuf, host);

		if (prevchar == ':')
		{
			const char *port = ++p; /* advance past host terminator */

			while (*p && *p != '/' && *p != '?' && *p != ',')
				++p;

			prevchar = *p;
			*p = '\0';

			appendPQExpBufferStr(&portbuf, port);
		}

		if (prevchar != ',')
			break;
		++p;					/* advance past comma separator */
		appendPQExpBufferChar(&hostbuf, ',');
		appendPQExpBufferChar(&portbuf, ',');
	}

	/* Save final values for host and port. */
	if (PQExpBufferDataBroken(hostbuf) || PQExpBufferDataBroken(portbuf))
		goto cleanup;
	if (hostbuf.data[0] &&
		!conninfo_storeval(options, "host", hostbuf.data,
						   errorMessage, false, true))
		goto cleanup;
	if (portbuf.data[0] &&
		!conninfo_storeval(options, "port", portbuf.data,
						   errorMessage, false, true))
		goto cleanup;

	if (prevchar && prevchar != '?')
	{
		const char *dbname = ++p;	/* advance past host terminator */

		/* Look for query parameters */
		while (*p && *p != '?')
			++p;

		prevchar = *p;
		*p = '\0';

		/*
		 * Avoid setting dbname to an empty string, as it forces the default
		 * value (username) and ignores $PGDATABASE, as opposed to not setting
		 * it at all.
		 */
		if (*dbname &&
			!conninfo_storeval(options, "dbname", dbname,
							   errorMessage, false, true))
			goto cleanup;
	}

	if (prevchar)
	{
		++p;					/* advance past terminator */

		if (!conninfo_uri_parse_params(p, options, errorMessage))
			goto cleanup;
	}

	/* everything parsed okay */
	retval = true;

cleanup:
	termPQExpBuffer(&hostbuf);
	termPQExpBuffer(&portbuf);
	if (buf)
		free(buf);
	return retval;
}