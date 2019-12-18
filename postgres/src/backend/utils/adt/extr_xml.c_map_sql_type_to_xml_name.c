#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  typname; int /*<<< orphan*/  typnamespace; int /*<<< orphan*/  typtype; } ;
struct TYPE_6__ {char const* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_type ;

/* Variables and functions */
#define  BOOLOID 142 
#define  BPCHAROID 141 
#define  DATEOID 140 
 int /*<<< orphan*/  ERROR ; 
#define  FLOAT4OID 139 
#define  FLOAT8OID 138 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
#define  INT2OID 137 
#define  INT4OID 136 
#define  INT8OID 135 
 int /*<<< orphan*/  MyDatabaseId ; 
#define  NUMERICOID 134 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TIMEOID 133 
#define  TIMESTAMPOID 132 
#define  TIMESTAMPTZOID 131 
#define  TIMETZOID 130 
 int /*<<< orphan*/  TYPEOID ; 
 int /*<<< orphan*/  TYPTYPE_DOMAIN ; 
#define  VARCHAROID 129 
 int /*<<< orphan*/  VARHDRSZ ; 
#define  XMLOID 128 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int,...) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_database_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 char* map_multipart_sql_identifier_to_xml_name (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
map_sql_type_to_xml_name(Oid typeoid, int typmod)
{
	StringInfoData result;

	initStringInfo(&result);

	switch (typeoid)
	{
		case BPCHAROID:
			if (typmod == -1)
				appendStringInfoString(&result, "CHAR");
			else
				appendStringInfo(&result, "CHAR_%d", typmod - VARHDRSZ);
			break;
		case VARCHAROID:
			if (typmod == -1)
				appendStringInfoString(&result, "VARCHAR");
			else
				appendStringInfo(&result, "VARCHAR_%d", typmod - VARHDRSZ);
			break;
		case NUMERICOID:
			if (typmod == -1)
				appendStringInfoString(&result, "NUMERIC");
			else
				appendStringInfo(&result, "NUMERIC_%d_%d",
								 ((typmod - VARHDRSZ) >> 16) & 0xffff,
								 (typmod - VARHDRSZ) & 0xffff);
			break;
		case INT4OID:
			appendStringInfoString(&result, "INTEGER");
			break;
		case INT2OID:
			appendStringInfoString(&result, "SMALLINT");
			break;
		case INT8OID:
			appendStringInfoString(&result, "BIGINT");
			break;
		case FLOAT4OID:
			appendStringInfoString(&result, "REAL");
			break;
		case FLOAT8OID:
			appendStringInfoString(&result, "DOUBLE");
			break;
		case BOOLOID:
			appendStringInfoString(&result, "BOOLEAN");
			break;
		case TIMEOID:
			if (typmod == -1)
				appendStringInfoString(&result, "TIME");
			else
				appendStringInfo(&result, "TIME_%d", typmod);
			break;
		case TIMETZOID:
			if (typmod == -1)
				appendStringInfoString(&result, "TIME_WTZ");
			else
				appendStringInfo(&result, "TIME_WTZ_%d", typmod);
			break;
		case TIMESTAMPOID:
			if (typmod == -1)
				appendStringInfoString(&result, "TIMESTAMP");
			else
				appendStringInfo(&result, "TIMESTAMP_%d", typmod);
			break;
		case TIMESTAMPTZOID:
			if (typmod == -1)
				appendStringInfoString(&result, "TIMESTAMP_WTZ");
			else
				appendStringInfo(&result, "TIMESTAMP_WTZ_%d", typmod);
			break;
		case DATEOID:
			appendStringInfoString(&result, "DATE");
			break;
		case XMLOID:
			appendStringInfoString(&result, "XML");
			break;
		default:
			{
				HeapTuple	tuple;
				Form_pg_type typtuple;

				tuple = SearchSysCache1(TYPEOID, ObjectIdGetDatum(typeoid));
				if (!HeapTupleIsValid(tuple))
					elog(ERROR, "cache lookup failed for type %u", typeoid);
				typtuple = (Form_pg_type) GETSTRUCT(tuple);

				appendStringInfoString(&result,
									   map_multipart_sql_identifier_to_xml_name((typtuple->typtype == TYPTYPE_DOMAIN) ? "Domain" : "UDT",
																				get_database_name(MyDatabaseId),
																				get_namespace_name(typtuple->typnamespace),
																				NameStr(typtuple->typname)));

				ReleaseSysCache(tuple);
			}
	}

	return result.data;
}