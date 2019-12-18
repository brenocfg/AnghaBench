#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {void* oid; void* tableoid; } ;
struct TYPE_21__ {void* name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_20__ {int remoteVersion; TYPE_4__* dopt; } ;
struct TYPE_19__ {scalar_t__ no_publications; } ;
struct TYPE_18__ {int /*<<< orphan*/  data; } ;
struct TYPE_17__ {int puballtables; int pubinsert; int pubupdate; int pubdelete; int pubtruncate; TYPE_6__ dobj; void* rolname; } ;
typedef  TYPE_2__ PublicationInfo ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_6__*) ; 
 int /*<<< orphan*/  DO_PUBLICATION ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  pg_log_warning (char*,void*) ; 
 TYPE_2__* pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  username_subquery ; 

void
getPublications(Archive *fout)
{
	DumpOptions *dopt = fout->dopt;
	PQExpBuffer query;
	PGresult   *res;
	PublicationInfo *pubinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_pubname;
	int			i_rolname;
	int			i_puballtables;
	int			i_pubinsert;
	int			i_pubupdate;
	int			i_pubdelete;
	int			i_pubtruncate;
	int			i,
				ntups;

	if (dopt->no_publications || fout->remoteVersion < 100000)
		return;

	query = createPQExpBuffer();

	resetPQExpBuffer(query);

	/* Get the publications. */
	if (fout->remoteVersion >= 110000)
		appendPQExpBuffer(query,
						  "SELECT p.tableoid, p.oid, p.pubname, "
						  "(%s p.pubowner) AS rolname, "
						  "p.puballtables, p.pubinsert, p.pubupdate, p.pubdelete, p.pubtruncate "
						  "FROM pg_publication p",
						  username_subquery);
	else
		appendPQExpBuffer(query,
						  "SELECT p.tableoid, p.oid, p.pubname, "
						  "(%s p.pubowner) AS rolname, "
						  "p.puballtables, p.pubinsert, p.pubupdate, p.pubdelete, false AS pubtruncate "
						  "FROM pg_publication p",
						  username_subquery);

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_pubname = PQfnumber(res, "pubname");
	i_rolname = PQfnumber(res, "rolname");
	i_puballtables = PQfnumber(res, "puballtables");
	i_pubinsert = PQfnumber(res, "pubinsert");
	i_pubupdate = PQfnumber(res, "pubupdate");
	i_pubdelete = PQfnumber(res, "pubdelete");
	i_pubtruncate = PQfnumber(res, "pubtruncate");

	pubinfo = pg_malloc(ntups * sizeof(PublicationInfo));

	for (i = 0; i < ntups; i++)
	{
		pubinfo[i].dobj.objType = DO_PUBLICATION;
		pubinfo[i].dobj.catId.tableoid =
			atooid(PQgetvalue(res, i, i_tableoid));
		pubinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&pubinfo[i].dobj);
		pubinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_pubname));
		pubinfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));
		pubinfo[i].puballtables =
			(strcmp(PQgetvalue(res, i, i_puballtables), "t") == 0);
		pubinfo[i].pubinsert =
			(strcmp(PQgetvalue(res, i, i_pubinsert), "t") == 0);
		pubinfo[i].pubupdate =
			(strcmp(PQgetvalue(res, i, i_pubupdate), "t") == 0);
		pubinfo[i].pubdelete =
			(strcmp(PQgetvalue(res, i, i_pubdelete), "t") == 0);
		pubinfo[i].pubtruncate =
			(strcmp(PQgetvalue(res, i, i_pubtruncate), "t") == 0);

		if (strlen(pubinfo[i].rolname) == 0)
			pg_log_warning("owner of publication \"%s\" appears to be invalid",
						   pubinfo[i].dobj.name);

		/* Decide whether we want to dump it */
		selectDumpableObject(&(pubinfo[i].dobj), fout);
	}
	PQclear(res);

	destroyPQExpBuffer(query);
}