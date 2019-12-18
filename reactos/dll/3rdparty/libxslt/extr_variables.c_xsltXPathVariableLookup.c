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
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStackElemPtr ;
typedef  int /*<<< orphan*/ * xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_9__ {int computed; int /*<<< orphan*/ * value; int /*<<< orphan*/  const* nameURI; int /*<<< orphan*/  const* name; struct TYPE_9__* next; } ;
struct TYPE_8__ {scalar_t__ varsNr; int varsBase; int /*<<< orphan*/  inst; scalar_t__ globalVars; TYPE_2__** varsTab; int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 int /*<<< orphan*/  stack_addr ; 
 int /*<<< orphan*/  stack_cmp ; 
 int /*<<< orphan*/ * xmlDictLookup (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xmlXPathObjectCopy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xsltEvalVariable (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/ * xsltGlobalVariableLookup (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,...) ; 

xmlXPathObjectPtr
xsltXPathVariableLookup(void *ctxt, const xmlChar *name,
	                const xmlChar *ns_uri) {
    xsltTransformContextPtr tctxt;
    xmlXPathObjectPtr valueObj = NULL;

    if ((ctxt == NULL) || (name == NULL))
	return(NULL);

#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(((xsltTransformContextPtr)ctxt),XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
	    "Lookup variable '%s'\n", name));
#endif

    tctxt = (xsltTransformContextPtr) ctxt;
    /*
    * Local variables/params ---------------------------------------------
    *
    * Do the lookup from the top of the stack, but
    * don't use params being computed in a call-param
    * First lookup expects the variable name and URI to
    * come from the disctionnary and hence pointer comparison.
    */
    if (tctxt->varsNr != 0) {
	int i;
	xsltStackElemPtr variable = NULL, cur;

	for (i = tctxt->varsNr; i > tctxt->varsBase; i--) {
	    cur = tctxt->varsTab[i-1];
	    if ((cur->name == name) && (cur->nameURI == ns_uri)) {
#if 0
		stack_addr++;
#endif
		variable = cur;
		goto local_variable_found;
	    }
	    cur = cur->next;
	}
	/*
	* Redo the lookup with interned strings to avoid string comparison.
	*
	* OPTIMIZE TODO: The problem here is, that if we request a
	*  global variable, then this will be also executed.
	*/
	{
	    const xmlChar *tmpName = name, *tmpNsName = ns_uri;

	    name = xmlDictLookup(tctxt->dict, name, -1);
	    if (ns_uri)
		ns_uri = xmlDictLookup(tctxt->dict, ns_uri, -1);
	    if ((tmpName != name) || (tmpNsName != ns_uri)) {
		for (i = tctxt->varsNr; i > tctxt->varsBase; i--) {
		    cur = tctxt->varsTab[i-1];
		    if ((cur->name == name) && (cur->nameURI == ns_uri)) {
#if 0
			stack_cmp++;
#endif
			variable = cur;
			goto local_variable_found;
		    }
		}
	    }
	}

local_variable_found:

	if (variable) {
	    if (variable->computed == 0) {

#ifdef WITH_XSLT_DEBUG_VARIABLE
		XSLT_TRACE(tctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
		    "uncomputed variable '%s'\n", name));
#endif
		variable->value = xsltEvalVariable(tctxt, variable, NULL);
		variable->computed = 1;
	    }
	    if (variable->value != NULL) {
		valueObj = xmlXPathObjectCopy(variable->value);
	    }
	    return(valueObj);
	}
    }
    /*
    * Global variables/params --------------------------------------------
    */
    if (tctxt->globalVars) {
	valueObj = xsltGlobalVariableLookup(tctxt, name, ns_uri);
    }

    if (valueObj == NULL) {

#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(tctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
		     "variable not found '%s'\n", name));
#endif

	if (ns_uri) {
	    xsltTransformError(tctxt, NULL, tctxt->inst,
		"Variable '{%s}%s' has not been declared.\n", ns_uri, name);
	} else {
	    xsltTransformError(tctxt, NULL, tctxt->inst,
		"Variable '%s' has not been declared.\n", name);
	}
    } else {

#ifdef WITH_XSLT_DEBUG_VARIABLE
	XSLT_TRACE(tctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
	    "found variable '%s'\n", name));
#endif
    }

    return(valueObj);
}