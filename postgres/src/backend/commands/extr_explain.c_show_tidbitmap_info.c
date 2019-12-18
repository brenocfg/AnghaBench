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
struct TYPE_7__ {scalar_t__ exact_pages; scalar_t__ lossy_pages; } ;
struct TYPE_6__ {scalar_t__ format; int indent; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ ExplainState ;
typedef  TYPE_2__ BitmapHeapScanState ;

/* Variables and functions */
 scalar_t__ EXPLAIN_FORMAT_TEXT ; 
 int /*<<< orphan*/  ExplainPropertyInteger (char*,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoSpaces (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
show_tidbitmap_info(BitmapHeapScanState *planstate, ExplainState *es)
{
	if (es->format != EXPLAIN_FORMAT_TEXT)
	{
		ExplainPropertyInteger("Exact Heap Blocks", NULL,
							   planstate->exact_pages, es);
		ExplainPropertyInteger("Lossy Heap Blocks", NULL,
							   planstate->lossy_pages, es);
	}
	else
	{
		if (planstate->exact_pages > 0 || planstate->lossy_pages > 0)
		{
			appendStringInfoSpaces(es->str, es->indent * 2);
			appendStringInfoString(es->str, "Heap Blocks:");
			if (planstate->exact_pages > 0)
				appendStringInfo(es->str, " exact=%ld", planstate->exact_pages);
			if (planstate->lossy_pages > 0)
				appendStringInfo(es->str, " lossy=%ld", planstate->lossy_pages);
			appendStringInfoChar(es->str, '\n');
		}
	}
}