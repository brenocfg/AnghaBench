#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  TYPE_1__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltStyleBasicItemVariablePtr ;
typedef  int /*<<< orphan*/  xsltStackElemPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  inst; int /*<<< orphan*/  ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 int /*<<< orphan*/  xsltAddStackElem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltBuildVariable (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int xsltCheckStackElem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xsltRegisterVariable(xsltTransformContextPtr ctxt,
		     xsltStylePreCompPtr castedComp,
		     xmlNodePtr tree, int isParam)
{
#ifdef XSLT_REFACTORED
    xsltStyleBasicItemVariablePtr comp =
	(xsltStyleBasicItemVariablePtr) castedComp;
#else
    xsltStylePreCompPtr comp = castedComp;
    int present;
#endif
    xsltStackElemPtr variable;

#ifdef XSLT_REFACTORED
    /*
    * REFACTORED NOTE: Redefinitions of vars/params are checked
    *  at compilation time in the refactored code.
    * xsl:with-param parameters are checked in xsltApplyXSLTTemplate().
    */
#else
    present = xsltCheckStackElem(ctxt, comp->name, comp->ns);
    if (isParam == 0) {
	if ((present != 0) && (present != 3)) {
	    /* TODO: report QName. */
	    xsltTransformError(ctxt, NULL, comp->inst,
		"XSLT-variable: Redefinition of variable '%s'.\n", comp->name);
	    return(0);
	}
    } else if (present != 0) {
	if ((present == 1) || (present == 2)) {
	    /* TODO: report QName. */
	    xsltTransformError(ctxt, NULL, comp->inst,
		"XSLT-param: Redefinition of parameter '%s'.\n", comp->name);
	    return(0);
	}
#ifdef WITH_XSLT_DEBUG_VARIABLE
	XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
		 "param %s defined by caller\n", comp->name));
#endif
	return(0);
    }
#endif /* else of XSLT_REFACTORED */

    variable = xsltBuildVariable(ctxt, (xsltStylePreCompPtr) comp, tree);
    xsltAddStackElem(ctxt, variable);
    return(0);
}