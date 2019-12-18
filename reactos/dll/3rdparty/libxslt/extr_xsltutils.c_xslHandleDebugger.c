#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  int /*<<< orphan*/  xsltTemplatePtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
struct TYPE_2__ {int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ xsltDebuggerCurrentCallbacks ; 

void
xslHandleDebugger(xmlNodePtr cur, xmlNodePtr node, xsltTemplatePtr templ,
	          xsltTransformContextPtr ctxt)
{
    if (xsltDebuggerCurrentCallbacks.handler != NULL)
	xsltDebuggerCurrentCallbacks.handler(cur, node, templ, ctxt);
}