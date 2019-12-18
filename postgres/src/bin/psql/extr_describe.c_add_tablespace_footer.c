#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* footer; } ;
typedef  TYPE_2__ printTableContent ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {scalar_t__ data; } ;
typedef  TYPE_3__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 char RELKIND_INDEX ; 
 char RELKIND_MATVIEW ; 
 char RELKIND_PARTITIONED_INDEX ; 
 char RELKIND_PARTITIONED_TABLE ; 
 char RELKIND_RELATION ; 
 char RELKIND_TOASTVALUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  printTableAddFooter (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printTableSetFooter (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_3__*) ; 

__attribute__((used)) static void
add_tablespace_footer(printTableContent *const cont, char relkind,
					  Oid tablespace, const bool newline)
{
	/* relkinds for which we support tablespaces */
	if (relkind == RELKIND_RELATION ||
		relkind == RELKIND_MATVIEW ||
		relkind == RELKIND_INDEX ||
		relkind == RELKIND_PARTITIONED_TABLE ||
		relkind == RELKIND_PARTITIONED_INDEX ||
		relkind == RELKIND_TOASTVALUE)
	{
		/*
		 * We ignore the database default tablespace so that users not using
		 * tablespaces don't need to know about them.  This case also covers
		 * pre-8.0 servers, for which tablespace will always be 0.
		 */
		if (tablespace != 0)
		{
			PGresult   *result = NULL;
			PQExpBufferData buf;

			initPQExpBuffer(&buf);
			printfPQExpBuffer(&buf,
							  "SELECT spcname FROM pg_catalog.pg_tablespace\n"
							  "WHERE oid = '%u';", tablespace);
			result = PSQLexec(buf.data);
			if (!result)
			{
				termPQExpBuffer(&buf);
				return;
			}
			/* Should always be the case, but.... */
			if (PQntuples(result) > 0)
			{
				if (newline)
				{
					/* Add the tablespace as a new footer */
					printfPQExpBuffer(&buf, _("Tablespace: \"%s\""),
									  PQgetvalue(result, 0, 0));
					printTableAddFooter(cont, buf.data);
				}
				else
				{
					/* Append the tablespace to the latest footer */
					printfPQExpBuffer(&buf, "%s", cont->footer->data);

					/*-------
					   translator: before this string there's an index description like
					   '"foo_pkey" PRIMARY KEY, btree (a)' */
					appendPQExpBuffer(&buf, _(", tablespace \"%s\""),
									  PQgetvalue(result, 0, 0));
					printTableSetFooter(cont, buf.data);
				}
			}
			PQclear(result);
			termPQExpBuffer(&buf);
		}
	}
}