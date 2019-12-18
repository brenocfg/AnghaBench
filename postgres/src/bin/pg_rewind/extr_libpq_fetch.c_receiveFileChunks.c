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
typedef  char int64 ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 scalar_t__ BYTEAOID ; 
 scalar_t__ INT8OID ; 
#define  PGRES_SINGLE_TUPLE 129 
#define  PGRES_TUPLES_OK 128 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int PQfformat (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PQftype (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ ) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQgetlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQresultErrorMessage (int /*<<< orphan*/ *) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 int PQsendQueryParams (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int PQsetSingleRowMode (int /*<<< orphan*/ ) ; 
 scalar_t__ TEXTOID ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  open_target_file (char*,int) ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 int /*<<< orphan*/  pg_free (char*) ; 
 int /*<<< orphan*/  pg_log_debug (char*,...) ; 
 char* pg_malloc (int) ; 
 char pg_ntoh64 (char) ; 
 int /*<<< orphan*/  remove_target_file (char*,int) ; 
 int /*<<< orphan*/  write_target_range (char*,char,int) ; 

__attribute__((used)) static void
receiveFileChunks(const char *sql)
{
	PGresult   *res;

	if (PQsendQueryParams(conn, sql, 0, NULL, NULL, NULL, NULL, 1) != 1)
		pg_fatal("could not send query: %s", PQerrorMessage(conn));

	pg_log_debug("getting file chunks");

	if (PQsetSingleRowMode(conn) != 1)
		pg_fatal("could not set libpq connection to single row mode");

	while ((res = PQgetResult(conn)) != NULL)
	{
		char	   *filename;
		int			filenamelen;
		int64		chunkoff;
		int			chunksize;
		char	   *chunk;

		switch (PQresultStatus(res))
		{
			case PGRES_SINGLE_TUPLE:
				break;

			case PGRES_TUPLES_OK:
				PQclear(res);
				continue;		/* final zero-row result */

			default:
				pg_fatal("unexpected result while fetching remote files: %s",
						 PQresultErrorMessage(res));
		}

		/* sanity check the result set */
		if (PQnfields(res) != 3 || PQntuples(res) != 1)
			pg_fatal("unexpected result set size while fetching remote files");

		if (PQftype(res, 0) != TEXTOID ||
			PQftype(res, 1) != INT8OID ||
			PQftype(res, 2) != BYTEAOID)
		{
			pg_fatal("unexpected data types in result set while fetching remote files: %u %u %u",
					 PQftype(res, 0), PQftype(res, 1), PQftype(res, 2));
		}

		if (PQfformat(res, 0) != 1 &&
			PQfformat(res, 1) != 1 &&
			PQfformat(res, 2) != 1)
		{
			pg_fatal("unexpected result format while fetching remote files");
		}

		if (PQgetisnull(res, 0, 0) ||
			PQgetisnull(res, 0, 1))
		{
			pg_fatal("unexpected null values in result while fetching remote files");
		}

		if (PQgetlength(res, 0, 1) != sizeof(int64))
			pg_fatal("unexpected result length while fetching remote files");

		/* Read result set to local variables */
		memcpy(&chunkoff, PQgetvalue(res, 0, 1), sizeof(int64));
		chunkoff = pg_ntoh64(chunkoff);
		chunksize = PQgetlength(res, 0, 2);

		filenamelen = PQgetlength(res, 0, 0);
		filename = pg_malloc(filenamelen + 1);
		memcpy(filename, PQgetvalue(res, 0, 0), filenamelen);
		filename[filenamelen] = '\0';

		chunk = PQgetvalue(res, 0, 2);

		/*
		 * If a file has been deleted on the source, remove it on the target
		 * as well.  Note that multiple unlink() calls may happen on the same
		 * file if multiple data chunks are associated with it, hence ignore
		 * unconditionally anything missing.  If this file is not a relation
		 * data file, then it has been already truncated when creating the
		 * file chunk list at the previous execution of the filemap.
		 */
		if (PQgetisnull(res, 0, 2))
		{
			pg_log_debug("received null value for chunk for file \"%s\", file has been deleted",
						 filename);
			remove_target_file(filename, true);
			pg_free(filename);
			PQclear(res);
			continue;
		}

		pg_log_debug("received chunk for file \"%s\", offset %lld, size %d",
					 filename, (long long int) chunkoff, chunksize);

		open_target_file(filename, false);

		write_target_range(chunk, chunkoff, chunksize);

		pg_free(filename);

		PQclear(res);
	}
}