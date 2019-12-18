#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int format; int indent; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ ExplainState ;

/* Variables and functions */
#define  EXPLAIN_FORMAT_JSON 131 
#define  EXPLAIN_FORMAT_TEXT 130 
#define  EXPLAIN_FORMAT_XML 129 
#define  EXPLAIN_FORMAT_YAML 128 
 int /*<<< orphan*/  ExplainJSONLineEnding (TYPE_1__*) ; 
 int /*<<< orphan*/  ExplainXMLTag (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ExplainYAMLLineStarting (TYPE_1__*) ; 
 int /*<<< orphan*/  X_CLOSE_IMMEDIATE ; 
 int /*<<< orphan*/  appendStringInfoSpaces (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  escape_json (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  escape_yaml (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
ExplainDummyGroup(const char *objtype, const char *labelname, ExplainState *es)
{
	switch (es->format)
	{
		case EXPLAIN_FORMAT_TEXT:
			/* nothing to do */
			break;

		case EXPLAIN_FORMAT_XML:
			ExplainXMLTag(objtype, X_CLOSE_IMMEDIATE, es);
			break;

		case EXPLAIN_FORMAT_JSON:
			ExplainJSONLineEnding(es);
			appendStringInfoSpaces(es->str, 2 * es->indent);
			if (labelname)
			{
				escape_json(es->str, labelname);
				appendStringInfoString(es->str, ": ");
			}
			escape_json(es->str, objtype);
			break;

		case EXPLAIN_FORMAT_YAML:
			ExplainYAMLLineStarting(es);
			if (labelname)
			{
				escape_yaml(es->str, labelname);
				appendStringInfoString(es->str, ": ");
			}
			else
			{
				appendStringInfoString(es->str, "- ");
			}
			escape_yaml(es->str, objtype);
			break;
	}
}