#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_12__ {int /*<<< orphan*/  attname; } ;
struct TYPE_11__ {int /*<<< orphan*/  rd_att; } ;
struct TYPE_10__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 char* generate_relation_name (TYPE_2__*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 char* quote_ident_cstr (int /*<<< orphan*/ ) ; 
 char* quote_literal_cstr (char*) ; 

__attribute__((used)) static char *
get_sql_delete(Relation rel, int *pkattnums, int pknumatts, char **tgt_pkattvals)
{
	char	   *relname;
	TupleDesc	tupdesc;
	StringInfoData buf;
	int			i;

	initStringInfo(&buf);

	/* get relation name including any needed schema prefix and quoting */
	relname = generate_relation_name(rel);

	tupdesc = rel->rd_att;

	appendStringInfo(&buf, "DELETE FROM %s WHERE ", relname);
	for (i = 0; i < pknumatts; i++)
	{
		int			pkattnum = pkattnums[i];
		Form_pg_attribute attr = TupleDescAttr(tupdesc, pkattnum);

		if (i > 0)
			appendStringInfoString(&buf, " AND ");

		appendStringInfoString(&buf,
							   quote_ident_cstr(NameStr(attr->attname)));

		if (tgt_pkattvals[i] != NULL)
			appendStringInfo(&buf, " = %s",
							 quote_literal_cstr(tgt_pkattvals[i]));
		else
			appendStringInfoString(&buf, " IS NULL");
	}

	return buf.data;
}