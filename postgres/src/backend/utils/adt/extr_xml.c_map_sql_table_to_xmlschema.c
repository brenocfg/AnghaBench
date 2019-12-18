#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_17__ {int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; scalar_t__ attisdropped; } ;
struct TYPE_16__ {int /*<<< orphan*/  relname; int /*<<< orphan*/  relnamespace; } ;
struct TYPE_15__ {char const* data; } ;
struct TYPE_14__ {int natts; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_class ;
typedef  TYPE_4__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,char*,...) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_database_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  list_make1 (TYPE_1__*) ; 
 char* map_multipart_sql_identifier_to_xml_name (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* map_sql_identifier_to_xml_name (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  map_sql_type_to_xml_name (int /*<<< orphan*/ ,int) ; 
 char* map_sql_typecoll_to_xmlschema_types (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsd_schema_element_end (TYPE_2__*) ; 
 int /*<<< orphan*/  xsd_schema_element_start (TYPE_2__*,char const*) ; 

__attribute__((used)) static const char *
map_sql_table_to_xmlschema(TupleDesc tupdesc, Oid relid, bool nulls,
						   bool tableforest, const char *targetns)
{
	int			i;
	char	   *xmltn;
	char	   *tabletypename;
	char	   *rowtypename;
	StringInfoData result;

	initStringInfo(&result);

	if (OidIsValid(relid))
	{
		HeapTuple	tuple;
		Form_pg_class reltuple;

		tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(relid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for relation %u", relid);
		reltuple = (Form_pg_class) GETSTRUCT(tuple);

		xmltn = map_sql_identifier_to_xml_name(NameStr(reltuple->relname),
											   true, false);

		tabletypename = map_multipart_sql_identifier_to_xml_name("TableType",
																 get_database_name(MyDatabaseId),
																 get_namespace_name(reltuple->relnamespace),
																 NameStr(reltuple->relname));

		rowtypename = map_multipart_sql_identifier_to_xml_name("RowType",
															   get_database_name(MyDatabaseId),
															   get_namespace_name(reltuple->relnamespace),
															   NameStr(reltuple->relname));

		ReleaseSysCache(tuple);
	}
	else
	{
		if (tableforest)
			xmltn = "row";
		else
			xmltn = "table";

		tabletypename = "TableType";
		rowtypename = "RowType";
	}

	xsd_schema_element_start(&result, targetns);

	appendStringInfoString(&result,
						   map_sql_typecoll_to_xmlschema_types(list_make1(tupdesc)));

	appendStringInfo(&result,
					 "<xsd:complexType name=\"%s\">\n"
					 "  <xsd:sequence>\n",
					 rowtypename);

	for (i = 0; i < tupdesc->natts; i++)
	{
		Form_pg_attribute att = TupleDescAttr(tupdesc, i);

		if (att->attisdropped)
			continue;
		appendStringInfo(&result,
						 "    <xsd:element name=\"%s\" type=\"%s\"%s></xsd:element>\n",
						 map_sql_identifier_to_xml_name(NameStr(att->attname),
														true, false),
						 map_sql_type_to_xml_name(att->atttypid, -1),
						 nulls ? " nillable=\"true\"" : " minOccurs=\"0\"");
	}

	appendStringInfoString(&result,
						   "  </xsd:sequence>\n"
						   "</xsd:complexType>\n\n");

	if (!tableforest)
	{
		appendStringInfo(&result,
						 "<xsd:complexType name=\"%s\">\n"
						 "  <xsd:sequence>\n"
						 "    <xsd:element name=\"row\" type=\"%s\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>\n"
						 "  </xsd:sequence>\n"
						 "</xsd:complexType>\n\n",
						 tabletypename, rowtypename);

		appendStringInfo(&result,
						 "<xsd:element name=\"%s\" type=\"%s\"/>\n\n",
						 xmltn, tabletypename);
	}
	else
		appendStringInfo(&result,
						 "<xsd:element name=\"%s\" type=\"%s\"/>\n\n",
						 xmltn, rowtypename);

	xsd_schema_element_end(&result);

	return result.data;
}