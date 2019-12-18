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
typedef  int /*<<< orphan*/ * xsltTransformContextPtr ;
typedef  TYPE_1__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltStyleItemParamPtr ;
typedef  TYPE_2__* xmlNodePtr ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  children; TYPE_1__* psvi; } ;
struct TYPE_6__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  XSLT_TRACE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltRegisterVariable (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,char*) ; 

void
xsltParseStylesheetParam(xsltTransformContextPtr ctxt, xmlNodePtr cur)
{
#ifdef XSLT_REFACTORED
    xsltStyleItemParamPtr comp;
#else
    xsltStylePreCompPtr comp;
#endif

    if ((cur == NULL) || (ctxt == NULL) || (cur->type != XML_ELEMENT_NODE))
	return;

    comp = cur->psvi;
    if ((comp == NULL) || (comp->name == NULL)) {
	xsltTransformError(ctxt, NULL, cur,
	    "Internal error in xsltParseStylesheetParam(): "
	    "The XSLT 'param' declaration was not compiled correctly.\n");
	return;
    }

#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
	"Registering param %s\n", comp->name));
#endif

    xsltRegisterVariable(ctxt, (xsltStylePreCompPtr) comp, cur->children, 1);
}