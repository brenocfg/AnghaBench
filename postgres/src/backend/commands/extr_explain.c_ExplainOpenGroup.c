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
struct TYPE_6__ {int format; int indent; void* grouping_stack; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ ExplainState ;

/* Variables and functions */
#define  EXPLAIN_FORMAT_JSON 131 
#define  EXPLAIN_FORMAT_TEXT 130 
#define  EXPLAIN_FORMAT_XML 129 
#define  EXPLAIN_FORMAT_YAML 128 
 int /*<<< orphan*/  ExplainJSONLineEnding (TYPE_1__*) ; 
 int /*<<< orphan*/  ExplainXMLTag (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ExplainYAMLLineStarting (TYPE_1__*) ; 
 int /*<<< orphan*/  X_OPENING ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoSpaces (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  escape_json (int /*<<< orphan*/ ,char const*) ; 
 void* lcons_int (int,void*) ; 

void
ExplainOpenGroup(const char *objtype, const char *labelname,
				 bool labeled, ExplainState *es)
{
	switch (es->format)
	{
		case EXPLAIN_FORMAT_TEXT:
			/* nothing to do */
			break;

		case EXPLAIN_FORMAT_XML:
			ExplainXMLTag(objtype, X_OPENING, es);
			es->indent++;
			break;

		case EXPLAIN_FORMAT_JSON:
			ExplainJSONLineEnding(es);
			appendStringInfoSpaces(es->str, 2 * es->indent);
			if (labelname)
			{
				escape_json(es->str, labelname);
				appendStringInfoString(es->str, ": ");
			}
			appendStringInfoChar(es->str, labeled ? '{' : '[');

			/*
			 * In JSON format, the grouping_stack is an integer list.  0 means
			 * we've emitted nothing at this grouping level, 1 means we've
			 * emitted something (and so the next item needs a comma). See
			 * ExplainJSONLineEnding().
			 */
			es->grouping_stack = lcons_int(0, es->grouping_stack);
			es->indent++;
			break;

		case EXPLAIN_FORMAT_YAML:

			/*
			 * In YAML format, the grouping stack is an integer list.  0 means
			 * we've emitted nothing at this grouping level AND this grouping
			 * level is unlabelled and must be marked with "- ".  See
			 * ExplainYAMLLineStarting().
			 */
			ExplainYAMLLineStarting(es);
			if (labelname)
			{
				appendStringInfo(es->str, "%s: ", labelname);
				es->grouping_stack = lcons_int(1, es->grouping_stack);
			}
			else
			{
				appendStringInfoString(es->str, "- ");
				es->grouping_stack = lcons_int(0, es->grouping_stack);
			}
			es->indent++;
			break;
	}
}