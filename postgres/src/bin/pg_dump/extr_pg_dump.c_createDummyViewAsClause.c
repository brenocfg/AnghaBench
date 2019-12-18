#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numatts; int /*<<< orphan*/ * attnames; int /*<<< orphan*/ * attcollation; int /*<<< orphan*/ * atttypnames; } ;
typedef  TYPE_1__ TableInfo ;
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  int /*<<< orphan*/  CollInfo ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  createPQExpBuffer () ; 
 int /*<<< orphan*/ * findCollationByOid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmtId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmtQualifiedDumpable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PQExpBuffer
createDummyViewAsClause(Archive *fout, TableInfo *tbinfo)
{
	PQExpBuffer result = createPQExpBuffer();
	int			j;

	appendPQExpBufferStr(result, "SELECT");

	for (j = 0; j < tbinfo->numatts; j++)
	{
		if (j > 0)
			appendPQExpBufferChar(result, ',');
		appendPQExpBufferStr(result, "\n    ");

		appendPQExpBuffer(result, "NULL::%s", tbinfo->atttypnames[j]);

		/*
		 * Must add collation if not default for the type, because CREATE OR
		 * REPLACE VIEW won't change it
		 */
		if (OidIsValid(tbinfo->attcollation[j]))
		{
			CollInfo   *coll;

			coll = findCollationByOid(tbinfo->attcollation[j]);
			if (coll)
				appendPQExpBuffer(result, " COLLATE %s",
								  fmtQualifiedDumpable(coll));
		}

		appendPQExpBuffer(result, " AS %s", fmtId(tbinfo->attnames[j]));
	}

	return result;
}