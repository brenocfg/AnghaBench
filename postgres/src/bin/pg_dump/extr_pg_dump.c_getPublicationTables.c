#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  oid; } ;
struct TYPE_28__ {int dump; int /*<<< orphan*/  name; TYPE_4__* namespace; TYPE_2__ catId; } ;
struct TYPE_29__ {scalar_t__ relkind; TYPE_5__ dobj; } ;
typedef  TYPE_6__ TableInfo ;
struct TYPE_32__ {scalar_t__ no_publications; } ;
struct TYPE_31__ {int /*<<< orphan*/  data; } ;
struct TYPE_26__ {void* oid; void* tableoid; } ;
struct TYPE_23__ {int /*<<< orphan*/  name; TYPE_4__* namespace; TYPE_3__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_30__ {TYPE_11__ dobj; TYPE_6__* pubtable; int /*<<< orphan*/  pubname; } ;
struct TYPE_24__ {int /*<<< orphan*/  name; } ;
struct TYPE_27__ {TYPE_1__ dobj; } ;
struct TYPE_22__ {int remoteVersion; TYPE_9__* dopt; } ;
typedef  TYPE_7__ PublicationRelInfo ;
typedef  TYPE_8__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_9__ DumpOptions ;
typedef  TYPE_10__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_11__*) ; 
 int /*<<< orphan*/  DO_PUBLICATION_REL ; 
 int DUMP_COMPONENT_DEFINITION ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_8__*,char*,int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_8__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_8__*) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* pg_malloc (int) ; 
 int /*<<< orphan*/  pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_8__*) ; 
 int /*<<< orphan*/  selectDumpablePublicationTable (TYPE_11__*,TYPE_10__*) ; 

void
getPublicationTables(Archive *fout, TableInfo tblinfo[], int numTables)
{
	PQExpBuffer query;
	PGresult   *res;
	PublicationRelInfo *pubrinfo;
	DumpOptions *dopt = fout->dopt;
	int			i_tableoid;
	int			i_oid;
	int			i_pubname;
	int			i,
				j,
				ntups;

	if (dopt->no_publications || fout->remoteVersion < 100000)
		return;

	query = createPQExpBuffer();

	for (i = 0; i < numTables; i++)
	{
		TableInfo  *tbinfo = &tblinfo[i];

		/* Only plain tables can be aded to publications. */
		if (tbinfo->relkind != RELKIND_RELATION)
			continue;

		/*
		 * Ignore publication membership of tables whose definitions are not
		 * to be dumped.
		 */
		if (!(tbinfo->dobj.dump & DUMP_COMPONENT_DEFINITION))
			continue;

		pg_log_info("reading publication membership for table \"%s.%s\"",
					tbinfo->dobj.namespace->dobj.name,
					tbinfo->dobj.name);

		resetPQExpBuffer(query);

		/* Get the publication membership for the table. */
		appendPQExpBuffer(query,
						  "SELECT pr.tableoid, pr.oid, p.pubname "
						  "FROM pg_publication_rel pr, pg_publication p "
						  "WHERE pr.prrelid = '%u'"
						  "  AND p.oid = pr.prpubid",
						  tbinfo->dobj.catId.oid);
		res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

		ntups = PQntuples(res);

		if (ntups == 0)
		{
			/*
			 * Table is not member of any publications. Clean up and return.
			 */
			PQclear(res);
			continue;
		}

		i_tableoid = PQfnumber(res, "tableoid");
		i_oid = PQfnumber(res, "oid");
		i_pubname = PQfnumber(res, "pubname");

		pubrinfo = pg_malloc(ntups * sizeof(PublicationRelInfo));

		for (j = 0; j < ntups; j++)
		{
			pubrinfo[j].dobj.objType = DO_PUBLICATION_REL;
			pubrinfo[j].dobj.catId.tableoid =
				atooid(PQgetvalue(res, j, i_tableoid));
			pubrinfo[j].dobj.catId.oid = atooid(PQgetvalue(res, j, i_oid));
			AssignDumpId(&pubrinfo[j].dobj);
			pubrinfo[j].dobj.namespace = tbinfo->dobj.namespace;
			pubrinfo[j].dobj.name = tbinfo->dobj.name;
			pubrinfo[j].pubname = pg_strdup(PQgetvalue(res, j, i_pubname));
			pubrinfo[j].pubtable = tbinfo;

			/* Decide whether we want to dump it */
			selectDumpablePublicationTable(&(pubrinfo[j].dobj), fout);
		}
		PQclear(res);
	}
	destroyPQExpBuffer(query);
}