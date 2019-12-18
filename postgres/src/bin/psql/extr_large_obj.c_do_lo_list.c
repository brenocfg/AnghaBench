#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tuples_only; } ;
struct TYPE_6__ {int translate_header; int /*<<< orphan*/  title; int /*<<< orphan*/ * nullPrint; TYPE_1__ topt; } ;
typedef  TYPE_2__ printQueryOpt ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; TYPE_2__ popt; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* gettext_noop (char*) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ pset ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 

bool
do_lo_list(void)
{
	PGresult   *res;
	char		buf[1024];
	printQueryOpt myopt = pset.popt;

	if (pset.sversion >= 90000)
	{
		snprintf(buf, sizeof(buf),
				 "SELECT oid as \"%s\",\n"
				 "  pg_catalog.pg_get_userbyid(lomowner) as \"%s\",\n"
				 "  pg_catalog.obj_description(oid, 'pg_largeobject') as \"%s\"\n"
				 "  FROM pg_catalog.pg_largeobject_metadata "
				 "  ORDER BY oid",
				 gettext_noop("ID"),
				 gettext_noop("Owner"),
				 gettext_noop("Description"));
	}
	else
	{
		snprintf(buf, sizeof(buf),
				 "SELECT loid as \"%s\",\n"
				 "  pg_catalog.obj_description(loid, 'pg_largeobject') as \"%s\"\n"
				 "FROM (SELECT DISTINCT loid FROM pg_catalog.pg_largeobject) x\n"
				 "ORDER BY 1",
				 gettext_noop("ID"),
				 gettext_noop("Description"));
	}

	res = PSQLexec(buf);
	if (!res)
		return false;

	myopt.topt.tuples_only = false;
	myopt.nullPrint = NULL;
	myopt.title = _("Large objects");
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}