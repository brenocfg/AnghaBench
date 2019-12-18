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
typedef  int OidOptions ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQueryForSingleRow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 char* g_opaque_type ; 
 char* pg_strdup (char*) ; 
 int zeroAsAny ; 
 int zeroAsNone ; 
 int zeroAsOpaque ; 
 int zeroAsStar ; 

__attribute__((used)) static char *
getFormattedTypeName(Archive *fout, Oid oid, OidOptions opts)
{
	char	   *result;
	PQExpBuffer query;
	PGresult   *res;

	if (oid == 0)
	{
		if ((opts & zeroAsOpaque) != 0)
			return pg_strdup(g_opaque_type);
		else if ((opts & zeroAsAny) != 0)
			return pg_strdup("'any'");
		else if ((opts & zeroAsStar) != 0)
			return pg_strdup("*");
		else if ((opts & zeroAsNone) != 0)
			return pg_strdup("NONE");
	}

	query = createPQExpBuffer();
	appendPQExpBuffer(query, "SELECT pg_catalog.format_type('%u'::pg_catalog.oid, NULL)",
					  oid);

	res = ExecuteSqlQueryForSingleRow(fout, query->data);

	/* result of format_type is already quoted */
	result = pg_strdup(PQgetvalue(res, 0, 0));

	PQclear(res);
	destroyPQExpBuffer(query);

	return result;
}