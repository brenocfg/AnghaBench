#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQueryForSingleRow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  fmtId (int /*<<< orphan*/ ) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
get_language_name(Archive *fout, Oid langid)
{
	PQExpBuffer query;
	PGresult   *res;
	char	   *lanname;

	query = createPQExpBuffer();
	appendPQExpBuffer(query, "SELECT lanname FROM pg_language WHERE oid = %u", langid);
	res = ExecuteSqlQueryForSingleRow(fout, query->data);
	lanname = pg_strdup(fmtId(PQgetvalue(res, 0, 0)));
	destroyPQExpBuffer(query);
	PQclear(res);

	return lanname;
}