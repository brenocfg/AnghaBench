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
typedef  int /*<<< orphan*/ * xsltTransformContextPtr ;
typedef  TYPE_1__* xsltStackElemPtr ;
typedef  int /*<<< orphan*/ * xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {int computed; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_TRACE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 int /*<<< orphan*/ * xmlXPathObjectCopy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xsltEvalVariable (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/ * xsltGlobalVariableLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_1__* xsltStackLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

xmlXPathObjectPtr
xsltVariableLookup(xsltTransformContextPtr ctxt, const xmlChar *name,
		   const xmlChar *ns_uri) {
    xsltStackElemPtr elem;

    if (ctxt == NULL)
	return(NULL);

    elem = xsltStackLookup(ctxt, name, ns_uri);
    if (elem == NULL) {
	return(xsltGlobalVariableLookup(ctxt, name, ns_uri));
    }
    if (elem->computed == 0) {
#ifdef WITH_XSLT_DEBUG_VARIABLE
	XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
		         "uncomputed variable %s\n", name));
#endif
        elem->value = xsltEvalVariable(ctxt, elem, NULL);
	elem->computed = 1;
    }
    if (elem->value != NULL)
	return(xmlXPathObjectCopy(elem->value));
#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
		     "variable not found %s\n", name));
#endif
    return(NULL);
}