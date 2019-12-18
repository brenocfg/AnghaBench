#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t whichhost; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  sslmode; TYPE_1__* connhost; } ;
struct TYPE_5__ {char* host; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  libpq_ngettext (char*,char*,int) ; 
 int pgtls_verify_peer_name_matches_certificate_guts (TYPE_2__*,int*,char**) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

bool
pq_verify_peer_name_matches_certificate(PGconn *conn)
{
	char	   *host = conn->connhost[conn->whichhost].host;
	int			rc;
	int			names_examined = 0;
	char	   *first_name = NULL;

	/*
	 * If told not to verify the peer name, don't do it. Return true
	 * indicating that the verification was successful.
	 */
	if (strcmp(conn->sslmode, "verify-full") != 0)
		return true;

	/* Check that we have a hostname to compare with. */
	if (!(host && host[0] != '\0'))
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("host name must be specified for a verified SSL connection\n"));
		return false;
	}

	rc = pgtls_verify_peer_name_matches_certificate_guts(conn, &names_examined, &first_name);

	if (rc == 0)
	{
		/*
		 * No match. Include the name from the server certificate in the error
		 * message, to aid debugging broken configurations. If there are
		 * multiple names, only print the first one to avoid an overly long
		 * error message.
		 */
		if (names_examined > 1)
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_ngettext("server certificate for \"%s\" (and %d other name) does not match host name \"%s\"\n",
											 "server certificate for \"%s\" (and %d other names) does not match host name \"%s\"\n",
											 names_examined - 1),
							  first_name, names_examined - 1, host);
		}
		else if (names_examined == 1)
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("server certificate for \"%s\" does not match host name \"%s\"\n"),
							  first_name, host);
		}
		else
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("could not get server's host name from server certificate\n"));
		}
	}

	/* clean up */
	if (first_name)
		free(first_name);

	return (rc == 1);
}