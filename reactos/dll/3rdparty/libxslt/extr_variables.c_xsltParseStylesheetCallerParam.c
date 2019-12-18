#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltTransformContextPtr ;
typedef  TYPE_1__* xsltStylePreCompPtr ;
typedef  TYPE_1__* xsltStyleBasicItemVariablePtr ;
typedef  int /*<<< orphan*/ * xsltStackElemPtr ;
typedef  TYPE_3__* xmlNodePtr ;
struct TYPE_9__ {scalar_t__ type; struct TYPE_9__* children; scalar_t__ psvi; } ;
struct TYPE_8__ {int /*<<< orphan*/ * select; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  XSLT_TRACE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 int /*<<< orphan*/ * xsltBuildVariable (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,char*) ; 

xsltStackElemPtr
xsltParseStylesheetCallerParam(xsltTransformContextPtr ctxt, xmlNodePtr inst)
{
#ifdef XSLT_REFACTORED
    xsltStyleBasicItemVariablePtr comp;
#else
    xsltStylePreCompPtr comp;
#endif
    xmlNodePtr tree = NULL; /* The first child node of the instruction or
                               the instruction itself. */
    xsltStackElemPtr param = NULL;

    if ((ctxt == NULL) || (inst == NULL) || (inst->type != XML_ELEMENT_NODE))
	return(NULL);

#ifdef XSLT_REFACTORED
    comp = (xsltStyleBasicItemVariablePtr) inst->psvi;
#else
    comp = (xsltStylePreCompPtr) inst->psvi;
#endif

    if (comp == NULL) {
        xsltTransformError(ctxt, NULL, inst,
	    "Internal error in xsltParseStylesheetCallerParam(): "
	    "The XSLT 'with-param' instruction was not compiled.\n");
        return(NULL);
    }
    if (comp->name == NULL) {
	xsltTransformError(ctxt, NULL, inst,
	    "Internal error in xsltParseStylesheetCallerParam(): "
	    "XSLT 'with-param': The attribute 'name' was not compiled.\n");
	return(NULL);
    }

#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
	    "Handling xsl:with-param %s\n", comp->name));
#endif

    if (comp->select == NULL) {
	tree = inst->children;
    } else {
#ifdef WITH_XSLT_DEBUG_VARIABLE
	XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
	    "        select %s\n", comp->select));
#endif
	tree = inst;
    }

    param = xsltBuildVariable(ctxt, (xsltStylePreCompPtr) comp, tree);

    return(param);
}