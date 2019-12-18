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
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQueryForSingleRow (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
get_synchronized_snapshot(Archive *fout)
{
	char	   *query = "SELECT pg_catalog.pg_export_snapshot()";
	char	   *result;
	PGresult   *res;

	res = ExecuteSqlQueryForSingleRow(fout, query);
	result = pg_strdup(PQgetvalue(res, 0, 0));
	PQclear(res);

	return result;
}