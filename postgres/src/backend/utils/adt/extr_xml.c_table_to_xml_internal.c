#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  query_to_xml_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int,char const*,int) ; 
 int /*<<< orphan*/  regclassout ; 

__attribute__((used)) static StringInfo
table_to_xml_internal(Oid relid,
					  const char *xmlschema, bool nulls, bool tableforest,
					  const char *targetns, bool top_level)
{
	StringInfoData query;

	initStringInfo(&query);
	appendStringInfo(&query, "SELECT * FROM %s",
					 DatumGetCString(DirectFunctionCall1(regclassout,
														 ObjectIdGetDatum(relid))));
	return query_to_xml_internal(query.data, get_rel_name(relid),
								 xmlschema, nulls, tableforest,
								 targetns, top_level);
}