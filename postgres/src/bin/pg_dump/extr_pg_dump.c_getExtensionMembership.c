#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {void* oid; void* tableoid; } ;
struct TYPE_13__ {scalar_t__ oid; } ;
struct TYPE_14__ {TYPE_1__ catId; } ;
struct TYPE_17__ {TYPE_2__ dobj; } ;
struct TYPE_16__ {TYPE_5__* ext; TYPE_6__ catId; } ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  scalar_t__ Oid ;
typedef  TYPE_4__ ExtensionMemberId ;
typedef  TYPE_5__ ExtensionInfo ;
typedef  TYPE_6__ CatalogId ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 TYPE_5__* findExtensionByOid (scalar_t__) ; 
 int /*<<< orphan*/  pg_log_warning (char*,scalar_t__) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  setExtensionMembership (TYPE_4__*,int) ; 

void
getExtensionMembership(Archive *fout, ExtensionInfo extinfo[],
					   int numExtensions)
{
	PQExpBuffer query;
	PGresult   *res;
	int			ntups,
				nextmembers,
				i;
	int			i_classid,
				i_objid,
				i_refobjid;
	ExtensionMemberId *extmembers;
	ExtensionInfo *ext;

	/* Nothing to do if no extensions */
	if (numExtensions == 0)
		return;

	query = createPQExpBuffer();

	/* refclassid constraint is redundant but may speed the search */
	appendPQExpBufferStr(query, "SELECT "
						 "classid, objid, refobjid "
						 "FROM pg_depend "
						 "WHERE refclassid = 'pg_extension'::regclass "
						 "AND deptype = 'e' "
						 "ORDER BY 3");

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	i_classid = PQfnumber(res, "classid");
	i_objid = PQfnumber(res, "objid");
	i_refobjid = PQfnumber(res, "refobjid");

	extmembers = (ExtensionMemberId *) pg_malloc(ntups * sizeof(ExtensionMemberId));
	nextmembers = 0;

	/*
	 * Accumulate data into extmembers[].
	 *
	 * Since we ordered the SELECT by referenced ID, we can expect that
	 * multiple entries for the same extension will appear together; this
	 * saves on searches.
	 */
	ext = NULL;

	for (i = 0; i < ntups; i++)
	{
		CatalogId	objId;
		Oid			extId;

		objId.tableoid = atooid(PQgetvalue(res, i, i_classid));
		objId.oid = atooid(PQgetvalue(res, i, i_objid));
		extId = atooid(PQgetvalue(res, i, i_refobjid));

		if (ext == NULL ||
			ext->dobj.catId.oid != extId)
			ext = findExtensionByOid(extId);

		if (ext == NULL)
		{
			/* shouldn't happen */
			pg_log_warning("could not find referenced extension %u", extId);
			continue;
		}

		extmembers[nextmembers].catId = objId;
		extmembers[nextmembers].ext = ext;
		nextmembers++;
	}

	PQclear(res);

	/* Remember the data for use later */
	setExtensionMembership(extmembers, nextmembers);

	destroyPQExpBuffer(query);
}