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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 char* ERRCODE_UNDEFINED_TABLE ; 
 int /*<<< orphan*/  PART_HASH ; 
 int /*<<< orphan*/  PART_NONE ; 
 int /*<<< orphan*/  PART_RANGE ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PG_DIAG_SQLSTATE ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQdb (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PQntuples (int /*<<< orphan*/ *) ; 
 char* PQresultErrorField (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  partition_method ; 
 scalar_t__ partitions ; 
 scalar_t__ scale ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
GetTableInfo(PGconn *con, bool scale_given)
{
	PGresult   *res;

	/*
	 * get the scaling factor that should be same as count(*) from
	 * pgbench_branches if this is not a custom query
	 */
	res = PQexec(con, "select count(*) from pgbench_branches");
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		char	   *sqlState = PQresultErrorField(res, PG_DIAG_SQLSTATE);

		fprintf(stderr, "%s", PQerrorMessage(con));
		if (sqlState && strcmp(sqlState, ERRCODE_UNDEFINED_TABLE) == 0)
		{
			fprintf(stderr, "Perhaps you need to do initialization (\"pgbench -i\") in database \"%s\"\n", PQdb(con));
		}

		exit(1);
	}
	scale = atoi(PQgetvalue(res, 0, 0));
	if (scale < 0)
	{
		fprintf(stderr, "invalid count(*) from pgbench_branches: \"%s\"\n",
				PQgetvalue(res, 0, 0));
		exit(1);
	}
	PQclear(res);

	/* warn if we override user-given -s switch */
	if (scale_given)
		fprintf(stderr,
				"scale option ignored, using count from pgbench_branches table (%d)\n",
				scale);

	/*
	 * Get the partition information for the first "pgbench_accounts" table
	 * found in search_path.
	 *
	 * The result is empty if no "pgbench_accounts" is found.
	 *
	 * Otherwise, it always returns one row even if the table is not
	 * partitioned (in which case the partition strategy is NULL).
	 *
	 * The number of partitions can be 0 even for partitioned tables, if no
	 * partition is attached.
	 *
	 * We assume no partitioning on any failure, so as to avoid failing on an
	 * old version without "pg_partitioned_table".
	 */
	res = PQexec(con,
				 "select o.n, p.partstrat, pg_catalog.count(i.inhparent) "
				 "from pg_catalog.pg_class as c "
				 "join pg_catalog.pg_namespace as n on (n.oid = c.relnamespace) "
				 "cross join lateral (select pg_catalog.array_position(pg_catalog.current_schemas(true), n.nspname)) as o(n) "
				 "left join pg_catalog.pg_partitioned_table as p on (p.partrelid = c.oid) "
				 "left join pg_catalog.pg_inherits as i on (c.oid = i.inhparent) "
				 "where c.relname = 'pgbench_accounts' and o.n is not null "
				 "group by 1, 2 "
				 "order by 1 asc "
				 "limit 1");

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		/* probably an older version, coldly assume no partitioning */
		partition_method = PART_NONE;
		partitions = 0;
	}
	else if (PQntuples(res) == 0)
	{
		/*
		 * This case is unlikely as pgbench already found "pgbench_branches"
		 * above to compute the scale.
		 */
		fprintf(stderr,
				"no pgbench_accounts table found in search_path\n"
				"Perhaps you need to do initialization (\"pgbench -i\") in database \"%s\".\n", PQdb(con));
		exit(1);
	}
	else						/* PQntupes(res) == 1 */
	{
		/* normal case, extract partition information */
		if (PQgetisnull(res, 0, 1))
			partition_method = PART_NONE;
		else
		{
			char	   *ps = PQgetvalue(res, 0, 1);

			/* column must be there */
			Assert(ps != NULL);

			if (strcmp(ps, "r") == 0)
				partition_method = PART_RANGE;
			else if (strcmp(ps, "h") == 0)
				partition_method = PART_HASH;
			else
			{
				/* possibly a newer version with new partition method */
				fprintf(stderr, "unexpected partition method: \"%s\"\n", ps);
				exit(1);
			}
		}

		partitions = atoi(PQgetvalue(res, 0, 2));
	}

	PQclear(res);
}