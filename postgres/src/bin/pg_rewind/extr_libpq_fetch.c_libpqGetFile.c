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
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexecParams (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQgetlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQresultErrorMessage (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_fatal (char*,char const*,...) ; 
 int /*<<< orphan*/  pg_log_debug (char*,char const*,int) ; 
 char* pg_malloc (int) ; 

char *
libpqGetFile(const char *filename, size_t *filesize)
{
	PGresult   *res;
	char	   *result;
	int			len;
	const char *paramValues[1];

	paramValues[0] = filename;
	res = PQexecParams(conn, "SELECT pg_read_binary_file($1)",
					   1, NULL, paramValues, NULL, NULL, 1);

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
		pg_fatal("could not fetch remote file \"%s\": %s",
				 filename, PQresultErrorMessage(res));

	/* sanity check the result set */
	if (PQntuples(res) != 1 || PQgetisnull(res, 0, 0))
		pg_fatal("unexpected result set while fetching remote file \"%s\"",
				 filename);

	/* Read result to local variables */
	len = PQgetlength(res, 0, 0);
	result = pg_malloc(len + 1);
	memcpy(result, PQgetvalue(res, 0, 0), len);
	result[len] = '\0';

	PQclear(res);

	pg_log_debug("fetched file \"%s\", length %d", filename, len);

	if (filesize)
		*filesize = len;
	return result;
}