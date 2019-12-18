#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {void* oid; void* tableoid; } ;
struct TYPE_22__ {void* name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_21__ {int remoteVersion; TYPE_4__* dopt; } ;
struct TYPE_20__ {scalar_t__ no_subscriptions; } ;
struct TYPE_19__ {char* data; } ;
struct TYPE_18__ {TYPE_6__ dobj; void* rolname; void* subpublications; void* subsynccommit; int /*<<< orphan*/ * subslotname; void* subconninfo; } ;
typedef  TYPE_2__ SubscriptionInfo ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_6__*) ; 
 int /*<<< orphan*/  DO_SUBSCRIPTION ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  is_superuser (TYPE_5__*) ; 
 int /*<<< orphan*/  pg_log_warning (char*,...) ; 
 TYPE_2__* pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  username_subquery ; 

void
getSubscriptions(Archive *fout)
{
	DumpOptions *dopt = fout->dopt;
	PQExpBuffer query;
	PGresult   *res;
	SubscriptionInfo *subinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_subname;
	int			i_rolname;
	int			i_subconninfo;
	int			i_subslotname;
	int			i_subsynccommit;
	int			i_subpublications;
	int			i,
				ntups;

	if (dopt->no_subscriptions || fout->remoteVersion < 100000)
		return;

	if (!is_superuser(fout))
	{
		int			n;

		res = ExecuteSqlQuery(fout,
							  "SELECT count(*) FROM pg_subscription "
							  "WHERE subdbid = (SELECT oid FROM pg_database"
							  "                 WHERE datname = current_database())",
							  PGRES_TUPLES_OK);
		n = atoi(PQgetvalue(res, 0, 0));
		if (n > 0)
			pg_log_warning("subscriptions not dumped because current user is not a superuser");
		PQclear(res);
		return;
	}

	query = createPQExpBuffer();

	resetPQExpBuffer(query);

	/* Get the subscriptions in current database. */
	appendPQExpBuffer(query,
					  "SELECT s.tableoid, s.oid, s.subname,"
					  "(%s s.subowner) AS rolname, "
					  " s.subconninfo, s.subslotname, s.subsynccommit, "
					  " s.subpublications "
					  "FROM pg_subscription s "
					  "WHERE s.subdbid = (SELECT oid FROM pg_database"
					  "                   WHERE datname = current_database())",
					  username_subquery);
	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_subname = PQfnumber(res, "subname");
	i_rolname = PQfnumber(res, "rolname");
	i_subconninfo = PQfnumber(res, "subconninfo");
	i_subslotname = PQfnumber(res, "subslotname");
	i_subsynccommit = PQfnumber(res, "subsynccommit");
	i_subpublications = PQfnumber(res, "subpublications");

	subinfo = pg_malloc(ntups * sizeof(SubscriptionInfo));

	for (i = 0; i < ntups; i++)
	{
		subinfo[i].dobj.objType = DO_SUBSCRIPTION;
		subinfo[i].dobj.catId.tableoid =
			atooid(PQgetvalue(res, i, i_tableoid));
		subinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&subinfo[i].dobj);
		subinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_subname));
		subinfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));
		subinfo[i].subconninfo = pg_strdup(PQgetvalue(res, i, i_subconninfo));
		if (PQgetisnull(res, i, i_subslotname))
			subinfo[i].subslotname = NULL;
		else
			subinfo[i].subslotname = pg_strdup(PQgetvalue(res, i, i_subslotname));
		subinfo[i].subsynccommit =
			pg_strdup(PQgetvalue(res, i, i_subsynccommit));
		subinfo[i].subpublications =
			pg_strdup(PQgetvalue(res, i, i_subpublications));

		if (strlen(subinfo[i].rolname) == 0)
			pg_log_warning("owner of subscription \"%s\" appears to be invalid",
						   subinfo[i].dobj.name);

		/* Decide whether we want to dump it */
		selectDumpableObject(&(subinfo[i].dobj), fout);
	}
	PQclear(res);

	destroyPQExpBuffer(query);
}