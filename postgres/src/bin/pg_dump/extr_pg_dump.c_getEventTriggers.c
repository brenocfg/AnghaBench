#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void* oid; void* tableoid; } ;
struct TYPE_18__ {int /*<<< orphan*/  dump; void* name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_17__ {int remoteVersion; } ;
struct TYPE_16__ {TYPE_5__ dobj; int /*<<< orphan*/  evtenabled; void* evtfname; void* evttags; void* evtowner; void* evtevent; void* evtname; } ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ EventTriggerInfo ;
typedef  TYPE_4__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_5__*) ; 
 int /*<<< orphan*/  DO_EVENT_TRIGGER ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ *) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  username_subquery ; 

EventTriggerInfo *
getEventTriggers(Archive *fout, int *numEventTriggers)
{
	int			i;
	PQExpBuffer query;
	PGresult   *res;
	EventTriggerInfo *evtinfo;
	int			i_tableoid,
				i_oid,
				i_evtname,
				i_evtevent,
				i_evtowner,
				i_evttags,
				i_evtfname,
				i_evtenabled;
	int			ntups;

	/* Before 9.3, there are no event triggers */
	if (fout->remoteVersion < 90300)
	{
		*numEventTriggers = 0;
		return NULL;
	}

	query = createPQExpBuffer();

	appendPQExpBuffer(query,
					  "SELECT e.tableoid, e.oid, evtname, evtenabled, "
					  "evtevent, (%s evtowner) AS evtowner, "
					  "array_to_string(array("
					  "select quote_literal(x) "
					  " from unnest(evttags) as t(x)), ', ') as evttags, "
					  "e.evtfoid::regproc as evtfname "
					  "FROM pg_event_trigger e "
					  "ORDER BY e.oid",
					  username_subquery);

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	*numEventTriggers = ntups;

	evtinfo = (EventTriggerInfo *) pg_malloc(ntups * sizeof(EventTriggerInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_evtname = PQfnumber(res, "evtname");
	i_evtevent = PQfnumber(res, "evtevent");
	i_evtowner = PQfnumber(res, "evtowner");
	i_evttags = PQfnumber(res, "evttags");
	i_evtfname = PQfnumber(res, "evtfname");
	i_evtenabled = PQfnumber(res, "evtenabled");

	for (i = 0; i < ntups; i++)
	{
		evtinfo[i].dobj.objType = DO_EVENT_TRIGGER;
		evtinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		evtinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&evtinfo[i].dobj);
		evtinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_evtname));
		evtinfo[i].evtname = pg_strdup(PQgetvalue(res, i, i_evtname));
		evtinfo[i].evtevent = pg_strdup(PQgetvalue(res, i, i_evtevent));
		evtinfo[i].evtowner = pg_strdup(PQgetvalue(res, i, i_evtowner));
		evtinfo[i].evttags = pg_strdup(PQgetvalue(res, i, i_evttags));
		evtinfo[i].evtfname = pg_strdup(PQgetvalue(res, i, i_evtfname));
		evtinfo[i].evtenabled = *(PQgetvalue(res, i, i_evtenabled));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(evtinfo[i].dobj), fout);

		/* Event Triggers do not currently have ACLs. */
		evtinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return evtinfo;
}