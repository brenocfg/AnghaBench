#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  header; } ;
struct TYPE_12__ {scalar_t__ lax; int /*<<< orphan*/  expr; } ;
struct TYPE_11__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ JsonPathParseResult ;
typedef  TYPE_3__ JsonPath ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  JSONPATH_HDRSZ ; 
 int /*<<< orphan*/  JSONPATH_LAX ; 
 int /*<<< orphan*/  JSONPATH_VERSION ; 
 int /*<<< orphan*/  PG_RETURN_JSONPATH_P (TYPE_3__*) ; 
 int /*<<< orphan*/  SET_VARSIZE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoSpaces (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enlargeStringInfo (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char*) ; 
 int /*<<< orphan*/  flattenJsonPathParseItem (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 TYPE_2__* parsejsonpath (char*,int) ; 

__attribute__((used)) static Datum
jsonPathFromCstring(char *in, int len)
{
	JsonPathParseResult *jsonpath = parsejsonpath(in, len);
	JsonPath   *res;
	StringInfoData buf;

	initStringInfo(&buf);
	enlargeStringInfo(&buf, 4 * len /* estimation */ );

	appendStringInfoSpaces(&buf, JSONPATH_HDRSZ);

	if (!jsonpath)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"", "jsonpath",
						in)));

	flattenJsonPathParseItem(&buf, jsonpath->expr, 0, false);

	res = (JsonPath *) buf.data;
	SET_VARSIZE(res, buf.len);
	res->header = JSONPATH_VERSION;
	if (jsonpath->lax)
		res->header |= JSONPATH_LAX;

	PG_RETURN_JSONPATH_P(res);
}