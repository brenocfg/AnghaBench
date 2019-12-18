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
struct TYPE_5__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  map_sql_identifier_to_xml_name (char const*,int,int) ; 

__attribute__((used)) static char *
map_multipart_sql_identifier_to_xml_name(const char *a, const char *b, const char *c, const char *d)
{
	StringInfoData result;

	initStringInfo(&result);

	if (a)
		appendStringInfoString(&result,
							   map_sql_identifier_to_xml_name(a, true, true));
	if (b)
		appendStringInfo(&result, ".%s",
						 map_sql_identifier_to_xml_name(b, true, true));
	if (c)
		appendStringInfo(&result, ".%s",
						 map_sql_identifier_to_xml_name(c, true, true));
	if (d)
		appendStringInfo(&result, ".%s",
						 map_sql_identifier_to_xml_name(d, true, true));

	return result.data;
}