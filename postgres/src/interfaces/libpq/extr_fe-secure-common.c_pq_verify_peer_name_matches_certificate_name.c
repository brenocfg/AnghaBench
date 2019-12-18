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
struct TYPE_5__ {size_t whichhost; int /*<<< orphan*/  errorMessage; TYPE_1__* connhost; } ;
struct TYPE_4__ {char* host; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ pg_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 scalar_t__ wildcard_certificate_match (char*,char*) ; 

int
pq_verify_peer_name_matches_certificate_name(PGconn *conn,
											 const char *namedata, size_t namelen,
											 char **store_name)
{
	char	   *name;
	int			result;
	char	   *host = conn->connhost[conn->whichhost].host;

	*store_name = NULL;

	if (!(host && host[0] != '\0'))
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("host name must be specified\n"));
		return -1;
	}

	/*
	 * There is no guarantee the string returned from the certificate is
	 * NULL-terminated, so make a copy that is.
	 */
	name = malloc(namelen + 1);
	if (name == NULL)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));
		return -1;
	}
	memcpy(name, namedata, namelen);
	name[namelen] = '\0';

	/*
	 * Reject embedded NULLs in certificate common or alternative name to
	 * prevent attacks like CVE-2009-4034.
	 */
	if (namelen != strlen(name))
	{
		free(name);
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("SSL certificate's name contains embedded null\n"));
		return -1;
	}

	if (pg_strcasecmp(name, host) == 0)
	{
		/* Exact name match */
		result = 1;
	}
	else if (wildcard_certificate_match(name, host))
	{
		/* Matched wildcard name */
		result = 1;
	}
	else
	{
		result = 0;
	}

	*store_name = name;
	return result;
}