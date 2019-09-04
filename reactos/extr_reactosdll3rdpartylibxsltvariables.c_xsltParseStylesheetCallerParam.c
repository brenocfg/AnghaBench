#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltTransformContextPtr ;
typedef  TYPE_1__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/ * xsltStackElemPtr ;
typedef  TYPE_2__* xmlNodePtr ;
struct TYPE_8__ {scalar_t__ type; struct TYPE_8__* children; scalar_t__ psvi; } ;
struct TYPE_7__ {int /*<<< orphan*/ * select; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/ * xsltBuildVariable (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,char*) ; 

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