#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int format; void* grouping_stack; int /*<<< orphan*/  str; int /*<<< orphan*/  indent; } ;
typedef  TYPE_1__ ExplainState ;

/* Variables and functions */
#define  EXPLAIN_FORMAT_JSON 131 
#define  EXPLAIN_FORMAT_TEXT 130 
#define  EXPLAIN_FORMAT_XML 129 
#define  EXPLAIN_FORMAT_YAML 128 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 void* list_delete_first (void*) ; 

void
ExplainEndOutput(ExplainState *es)
{
	switch (es->format)
	{
		case EXPLAIN_FORMAT_TEXT:
			/* nothing to do */
			break;

		case EXPLAIN_FORMAT_XML:
			es->indent--;
			appendStringInfoString(es->str, "</explain>");
			break;

		case EXPLAIN_FORMAT_JSON:
			es->indent--;
			appendStringInfoString(es->str, "\n]");
			es->grouping_stack = list_delete_first(es->grouping_stack);
			break;

		case EXPLAIN_FORMAT_YAML:
			es->grouping_stack = list_delete_first(es->grouping_stack);
			break;
	}
}