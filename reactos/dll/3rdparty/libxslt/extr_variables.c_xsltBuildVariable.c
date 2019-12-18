#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  TYPE_1__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltStyleBasicItemVariablePtr ;
typedef  TYPE_2__* xsltStackElemPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
struct TYPE_9__ {int computed; int /*<<< orphan*/  value; int /*<<< orphan*/  tree; int /*<<< orphan*/  nameURI; int /*<<< orphan*/ * select; int /*<<< orphan*/  name; TYPE_1__* comp; } ;
struct TYPE_8__ {int /*<<< orphan*/  ns; int /*<<< orphan*/ * select; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 int /*<<< orphan*/  xsltEvalVariable (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 TYPE_2__* xsltNewStackElem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static xsltStackElemPtr
xsltBuildVariable(xsltTransformContextPtr ctxt,
		  xsltStylePreCompPtr castedComp,
		  xmlNodePtr tree)
{
#ifdef XSLT_REFACTORED
    xsltStyleBasicItemVariablePtr comp =
	(xsltStyleBasicItemVariablePtr) castedComp;
#else
    xsltStylePreCompPtr comp = castedComp;
#endif
    xsltStackElemPtr elem;

#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
		     "Building variable %s", comp->name));
    if (comp->select != NULL)
	XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
			 " select %s", comp->select));
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext, "\n"));
#endif

    elem = xsltNewStackElem(ctxt);
    if (elem == NULL)
	return(NULL);
    elem->comp = (xsltStylePreCompPtr) comp;
    elem->name = comp->name;
    elem->select = comp->select;
    elem->nameURI = comp->ns;
    elem->tree = tree;
    elem->value = xsltEvalVariable(ctxt, elem,
	(xsltStylePreCompPtr) comp);
    elem->computed = 1;
    return(elem);
}