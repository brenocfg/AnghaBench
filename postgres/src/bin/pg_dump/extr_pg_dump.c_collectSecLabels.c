#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  objsubid; void* objoid; void* classoid; void* provider; void* label; } ;
typedef  TYPE_1__ SecLabelItem ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 void* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  atoi (void*) ; 
 void* atooid (void*) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 scalar_t__ pg_malloc (int) ; 

__attribute__((used)) static int
collectSecLabels(Archive *fout, SecLabelItem **items)
{
	PGresult   *res;
	PQExpBuffer query;
	int			i_label;
	int			i_provider;
	int			i_classoid;
	int			i_objoid;
	int			i_objsubid;
	int			ntups;
	int			i;
	SecLabelItem *labels;

	query = createPQExpBuffer();

	appendPQExpBufferStr(query,
						 "SELECT label, provider, classoid, objoid, objsubid "
						 "FROM pg_catalog.pg_seclabel "
						 "ORDER BY classoid, objoid, objsubid");

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	/* Construct lookup table containing OIDs in numeric form */
	i_label = PQfnumber(res, "label");
	i_provider = PQfnumber(res, "provider");
	i_classoid = PQfnumber(res, "classoid");
	i_objoid = PQfnumber(res, "objoid");
	i_objsubid = PQfnumber(res, "objsubid");

	ntups = PQntuples(res);

	labels = (SecLabelItem *) pg_malloc(ntups * sizeof(SecLabelItem));

	for (i = 0; i < ntups; i++)
	{
		labels[i].label = PQgetvalue(res, i, i_label);
		labels[i].provider = PQgetvalue(res, i, i_provider);
		labels[i].classoid = atooid(PQgetvalue(res, i, i_classoid));
		labels[i].objoid = atooid(PQgetvalue(res, i, i_objoid));
		labels[i].objsubid = atoi(PQgetvalue(res, i, i_objsubid));
	}

	/* Do NOT free the PGresult since we are keeping pointers into it */
	destroyPQExpBuffer(query);

	*items = labels;
	return ntups;
}