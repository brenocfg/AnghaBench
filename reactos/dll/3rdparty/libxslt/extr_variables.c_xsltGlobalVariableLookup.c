#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltStackElemPtr ;
typedef  int /*<<< orphan*/ * xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_11__ {scalar_t__ computed; scalar_t__ name; int /*<<< orphan*/ * value; TYPE_1__* comp; } ;
struct TYPE_10__ {int /*<<< orphan*/ * globalVars; int /*<<< orphan*/ * xpathCtxt; } ;
struct TYPE_9__ {int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 scalar_t__ xmlHashLookup2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xmlXPathObjectCopy (int /*<<< orphan*/ *) ; 
 scalar_t__ xsltComputingGlobalVarMarker ; 
 int /*<<< orphan*/ * xsltEvalGlobalVariable (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static xmlXPathObjectPtr
xsltGlobalVariableLookup(xsltTransformContextPtr ctxt, const xmlChar *name,
		         const xmlChar *ns_uri) {
    xsltStackElemPtr elem;
    xmlXPathObjectPtr ret = NULL;

    /*
     * Lookup the global variables in XPath global variable hash table
     */
    if ((ctxt->xpathCtxt == NULL) || (ctxt->globalVars == NULL))
	return(NULL);
    elem = (xsltStackElemPtr)
	    xmlHashLookup2(ctxt->globalVars, name, ns_uri);
    if (elem == NULL) {
#ifdef WITH_XSLT_DEBUG_VARIABLE
	XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
			 "global variable not found %s\n", name));
#endif
	return(NULL);
    }
    /*
    * URGENT TODO: Move the detection of recursive definitions
    * to compile-time.
    */
    if (elem->computed == 0) {
	if (elem->name == xsltComputingGlobalVarMarker) {
	    xsltTransformError(ctxt, NULL, elem->comp->inst,
		"Recursive definition of %s\n", name);
	    return(NULL);
	}
	ret = xsltEvalGlobalVariable(elem, ctxt);
    } else
	ret = elem->value;
    return(xmlXPathObjectCopy(ret));
}