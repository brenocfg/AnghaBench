#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int remoteVersion; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  EndBlob (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecuteSqlStatement (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * GetConnection (TYPE_1__*) ; 
 int /*<<< orphan*/  INV_READ ; 
 int LOBBUFSIZE ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StartBlob (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteData (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  atooid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lo_close (int /*<<< orphan*/ *,int) ; 
 int lo_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lo_read (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  pg_log_info (char*) ; 

__attribute__((used)) static int
dumpBlobs(Archive *fout, void *arg)
{
	const char *blobQry;
	const char *blobFetchQry;
	PGconn	   *conn = GetConnection(fout);
	PGresult   *res;
	char		buf[LOBBUFSIZE];
	int			ntups;
	int			i;
	int			cnt;

	pg_log_info("saving large objects");

	/*
	 * Currently, we re-fetch all BLOB OIDs using a cursor.  Consider scanning
	 * the already-in-memory dumpable objects instead...
	 */
	if (fout->remoteVersion >= 90000)
		blobQry =
			"DECLARE bloboid CURSOR FOR "
			"SELECT oid FROM pg_largeobject_metadata ORDER BY 1";
	else
		blobQry =
			"DECLARE bloboid CURSOR FOR "
			"SELECT DISTINCT loid FROM pg_largeobject ORDER BY 1";

	ExecuteSqlStatement(fout, blobQry);

	/* Command to fetch from cursor */
	blobFetchQry = "FETCH 1000 IN bloboid";

	do
	{
		/* Do a fetch */
		res = ExecuteSqlQuery(fout, blobFetchQry, PGRES_TUPLES_OK);

		/* Process the tuples, if any */
		ntups = PQntuples(res);
		for (i = 0; i < ntups; i++)
		{
			Oid			blobOid;
			int			loFd;

			blobOid = atooid(PQgetvalue(res, i, 0));
			/* Open the BLOB */
			loFd = lo_open(conn, blobOid, INV_READ);
			if (loFd == -1)
				fatal("could not open large object %u: %s",
					  blobOid, PQerrorMessage(conn));

			StartBlob(fout, blobOid);

			/* Now read it in chunks, sending data to archive */
			do
			{
				cnt = lo_read(conn, loFd, buf, LOBBUFSIZE);
				if (cnt < 0)
					fatal("error reading large object %u: %s",
						  blobOid, PQerrorMessage(conn));

				WriteData(fout, buf, cnt);
			} while (cnt > 0);

			lo_close(conn, loFd);

			EndBlob(fout, blobOid);
		}

		PQclear(res);
	} while (ntups > 0);

	return 1;
}