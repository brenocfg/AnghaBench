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
 int /*<<< orphan*/  ExplainXMLTag (char const*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ExplainYAMLLineStarting (TYPE_1__*) ; 
 int X_CLOSING ; 
 int X_NOWHITESPACE ; 
 int X_OPENING ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoSpaces (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  escape_json (int /*<<< orphan*/ ,char const*) ; 
 char* escape_xml (char const*) ; 
 int /*<<< orphan*/  escape_yaml (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static void
ExplainProperty(const char *qlabel, const char *unit, const char *value,
				bool numeric, ExplainState *es)
{
	switch (es->format)
	{
		case EXPLAIN_FORMAT_TEXT:
			appendStringInfoSpaces(es->str, es->indent * 2);
			if (unit)
				appendStringInfo(es->str, "%s: %s %s\n", qlabel, value, unit);
			else
				appendStringInfo(es->str, "%s: %s\n", qlabel, value);
			break;

		case EXPLAIN_FORMAT_XML:
			{
				char	   *str;

				appendStringInfoSpaces(es->str, es->indent * 2);
				ExplainXMLTag(qlabel, X_OPENING | X_NOWHITESPACE, es);
				str = escape_xml(value);
				appendStringInfoString(es->str, str);
				pfree(str);
				ExplainXMLTag(qlabel, X_CLOSING | X_NOWHITESPACE, es);
				appendStringInfoChar(es->str, '\n');
			}
			break;

		case EXPLAIN_FORMAT_JSON:
			ExplainJSONLineEnding(es);
			appendStringInfoSpaces(es->str, es->indent * 2);
			escape_json(es->str, qlabel);
			appendStringInfoString(es->str, ": ");
			if (numeric)
				appendStringInfoString(es->str, value);
			else
				escape_json(es->str, value);
			break;

		case EXPLAIN_FORMAT_YAML:
			ExplainYAMLLineStarting(es);
			appendStringInfo(es->str, "%s: ", qlabel);
			if (numeric)
				appendStringInfoString(es->str, value);
			else
				escape_yaml(es->str, value);
			break;
	}
}