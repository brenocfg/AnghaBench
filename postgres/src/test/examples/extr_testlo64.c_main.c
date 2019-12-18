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
typedef  int /*<<< orphan*/  PGconn ;
typedef  int Oid ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQsetdb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exit_nicely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ lo_export (int /*<<< orphan*/ *,int,char*) ; 
 int lo_import (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  my_truncate (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  overwrite (int /*<<< orphan*/ *,int,unsigned int,int) ; 
 int /*<<< orphan*/  pickout (int /*<<< orphan*/ *,int,unsigned int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char **argv)
{
	char	   *in_filename,
			   *out_filename,
			   *out_filename2;
	char	   *database;
	Oid			lobjOid;
	PGconn	   *conn;
	PGresult   *res;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s database_name in_filename out_filename out_filename2\n",
				argv[0]);
		exit(1);
	}

	database = argv[1];
	in_filename = argv[2];
	out_filename = argv[3];
	out_filename2 = argv[4];

	/*
	 * set up the connection
	 */
	conn = PQsetdb(NULL, NULL, NULL, NULL, database);

	/* check to see that the backend connection was successfully made */
	if (PQstatus(conn) != CONNECTION_OK)
	{
		fprintf(stderr, "Connection to database failed: %s",
				PQerrorMessage(conn));
		exit_nicely(conn);
	}

	/* Set always-secure search path, so malicious users can't take control. */
	res = PQexec(conn,
				 "SELECT pg_catalog.set_config('search_path', '', false)");
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "SET failed: %s", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
	}
	PQclear(res);

	res = PQexec(conn, "begin");
	PQclear(res);
	printf("importing file \"%s\" ...\n", in_filename);
/*	lobjOid = importFile(conn, in_filename); */
	lobjOid = lo_import(conn, in_filename);
	if (lobjOid == 0)
		fprintf(stderr, "%s\n", PQerrorMessage(conn));
	else
	{
		printf("\tas large object %u.\n", lobjOid);

		printf("picking out bytes 4294967000-4294968000 of the large object\n");
		pickout(conn, lobjOid, 4294967000U, 1000);

		printf("overwriting bytes 4294967000-4294968000 of the large object with X's\n");
		overwrite(conn, lobjOid, 4294967000U, 1000);

		printf("exporting large object to file \"%s\" ...\n", out_filename);
/*		exportFile(conn, lobjOid, out_filename); */
		if (lo_export(conn, lobjOid, out_filename) < 0)
			fprintf(stderr, "%s\n", PQerrorMessage(conn));

		printf("truncating to 3294968000 bytes\n");
		my_truncate(conn, lobjOid, 3294968000U);

		printf("exporting truncated large object to file \"%s\" ...\n", out_filename2);
		if (lo_export(conn, lobjOid, out_filename2) < 0)
			fprintf(stderr, "%s\n", PQerrorMessage(conn));
	}

	res = PQexec(conn, "end");
	PQclear(res);
	PQfinish(conn);
	return 0;
}