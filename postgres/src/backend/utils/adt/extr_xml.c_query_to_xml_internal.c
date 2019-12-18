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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DATA_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ SPI_OK_SELECT ; 
 int /*<<< orphan*/  SPI_connect () ; 
 scalar_t__ SPI_execute (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_finish () ; 
 scalar_t__ SPI_processed ; 
 int /*<<< orphan*/  SPI_sql_row_to_xmlelement (scalar_t__,int /*<<< orphan*/ ,char*,int,int,char const*,int) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  makeStringInfo () ; 
 char* map_sql_identifier_to_xml_name (char*,int,int) ; 
 int /*<<< orphan*/  xmldata_root_element_end (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmldata_root_element_start (int /*<<< orphan*/ ,char*,char const*,char const*,int) ; 

__attribute__((used)) static StringInfo
query_to_xml_internal(const char *query, char *tablename,
					  const char *xmlschema, bool nulls, bool tableforest,
					  const char *targetns, bool top_level)
{
	StringInfo	result;
	char	   *xmltn;
	uint64		i;

	if (tablename)
		xmltn = map_sql_identifier_to_xml_name(tablename, true, false);
	else
		xmltn = "table";

	result = makeStringInfo();

	SPI_connect();
	if (SPI_execute(query, true, 0) != SPI_OK_SELECT)
		ereport(ERROR,
				(errcode(ERRCODE_DATA_EXCEPTION),
				 errmsg("invalid query")));

	if (!tableforest)
	{
		xmldata_root_element_start(result, xmltn, xmlschema,
								   targetns, top_level);
		appendStringInfoChar(result, '\n');
	}

	if (xmlschema)
		appendStringInfo(result, "%s\n\n", xmlschema);

	for (i = 0; i < SPI_processed; i++)
		SPI_sql_row_to_xmlelement(i, result, tablename, nulls,
								  tableforest, targetns, top_level);

	if (!tableforest)
		xmldata_root_element_end(result, xmltn);

	SPI_finish();

	return result;
}