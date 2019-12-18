#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  query ;
struct TYPE_6__ {int ndbs; TYPE_2__* dbs; } ;
struct TYPE_8__ {TYPE_1__ dbarr; int /*<<< orphan*/  major_version; } ;
struct TYPE_7__ {char* db_tablespace; void* db_ctype; void* db_collate; int /*<<< orphan*/  db_encoding; void* db_name; int /*<<< orphan*/  db_oid; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_2__ DbInfo ;
typedef  TYPE_3__ ClusterInfo ;

/* Variables and functions */
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int QUERY_ALLOC ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  atooid (char*) ; 
 int /*<<< orphan*/ * connectToServer (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * executeQueryOrDie (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
get_db_infos(ClusterInfo *cluster)
{
	PGconn	   *conn = connectToServer(cluster, "template1");
	PGresult   *res;
	int			ntups;
	int			tupnum;
	DbInfo	   *dbinfos;
	int			i_datname,
				i_oid,
				i_encoding,
				i_datcollate,
				i_datctype,
				i_spclocation;
	char		query[QUERY_ALLOC];

	snprintf(query, sizeof(query),
			 "SELECT d.oid, d.datname, d.encoding, d.datcollate, d.datctype, "
			 "%s AS spclocation "
			 "FROM pg_catalog.pg_database d "
			 " LEFT OUTER JOIN pg_catalog.pg_tablespace t "
			 " ON d.dattablespace = t.oid "
			 "WHERE d.datallowconn = true "
	/* we don't preserve pg_database.oid so we sort by name */
			 "ORDER BY 2",
	/* 9.2 removed the spclocation column */
			 (GET_MAJOR_VERSION(cluster->major_version) <= 901) ?
			 "t.spclocation" : "pg_catalog.pg_tablespace_location(t.oid)");

	res = executeQueryOrDie(conn, "%s", query);

	i_oid = PQfnumber(res, "oid");
	i_datname = PQfnumber(res, "datname");
	i_encoding = PQfnumber(res, "encoding");
	i_datcollate = PQfnumber(res, "datcollate");
	i_datctype = PQfnumber(res, "datctype");
	i_spclocation = PQfnumber(res, "spclocation");

	ntups = PQntuples(res);
	dbinfos = (DbInfo *) pg_malloc(sizeof(DbInfo) * ntups);

	for (tupnum = 0; tupnum < ntups; tupnum++)
	{
		dbinfos[tupnum].db_oid = atooid(PQgetvalue(res, tupnum, i_oid));
		dbinfos[tupnum].db_name = pg_strdup(PQgetvalue(res, tupnum, i_datname));
		dbinfos[tupnum].db_encoding = atoi(PQgetvalue(res, tupnum, i_encoding));
		dbinfos[tupnum].db_collate = pg_strdup(PQgetvalue(res, tupnum, i_datcollate));
		dbinfos[tupnum].db_ctype = pg_strdup(PQgetvalue(res, tupnum, i_datctype));
		snprintf(dbinfos[tupnum].db_tablespace, sizeof(dbinfos[tupnum].db_tablespace), "%s",
				 PQgetvalue(res, tupnum, i_spclocation));
	}
	PQclear(res);

	PQfinish(conn);

	cluster->dbarr.dbs = dbinfos;
	cluster->dbarr.ndbs = ntups;
}