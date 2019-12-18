#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltStylesheetPtr ;
typedef  TYPE_4__* xsltStackElemPtr ;
typedef  int /*<<< orphan*/ * xmlXPathObjectPtr ;
typedef  TYPE_5__* xmlXPathContextPtr ;
typedef  int /*<<< orphan*/ * xmlXPathCompExprPtr ;
typedef  TYPE_6__* xmlNsPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
typedef  char xmlChar ;
struct TYPE_23__ {char* href; } ;
struct TYPE_22__ {int proximityPosition; int contextSize; int nsNr; TYPE_6__** namespaces; int /*<<< orphan*/  node; int /*<<< orphan*/  doc; } ;
struct TYPE_21__ {char const* name; char const* nameURI; int computed; int /*<<< orphan*/ * value; int /*<<< orphan*/ * tree; void* select; struct TYPE_21__* next; TYPE_1__* comp; } ;
struct TYPE_20__ {TYPE_4__* variables; int /*<<< orphan*/  doc; } ;
struct TYPE_19__ {int /*<<< orphan*/ * globalVars; int /*<<< orphan*/  dict; int /*<<< orphan*/  state; int /*<<< orphan*/  initialContextNode; int /*<<< orphan*/  initialContextDoc; TYPE_5__* xpathCtxt; TYPE_3__* style; } ;
struct TYPE_18__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ XSLT_FUNC_VARIABLE ; 
 int /*<<< orphan*/  XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  XSLT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 
 void* xmlDictLookup (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  xmlDocGetRootElement (int /*<<< orphan*/ ) ; 
 int xmlHashAddEntry2 (int /*<<< orphan*/ *,char const*,char const*,TYPE_4__*) ; 
 int /*<<< orphan*/ * xmlHashCreate (int) ; 
 void* xmlHashLookup2 (int /*<<< orphan*/ *,char const*,char const*) ; 
 TYPE_6__* xmlSearchNs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ xmlStrEqual (char const*,char const*) ; 
 int /*<<< orphan*/ * xmlXPathCompile (char const*) ; 
 int /*<<< orphan*/ * xmlXPathCompiledEval (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  xmlXPathDebugDumpObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlXPathFreeCompExpr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlXPathNewString (char const*) ; 
 int /*<<< orphan*/  xsltFreeStackElem (TYPE_4__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (scalar_t__,char*,char const*,char const*) ; 
 scalar_t__ xsltGenericDebugContext ; 
 TYPE_4__* xsltNewStackElem (int /*<<< orphan*/ *) ; 
 TYPE_3__* xsltNextImport (TYPE_3__*) ; 
 char* xsltSplitQName (int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static
int
xsltProcessUserParamInternal(xsltTransformContextPtr ctxt,
		             const xmlChar * name,
			     const xmlChar * value,
			     int eval) {

    xsltStylesheetPtr style;
    const xmlChar *prefix;
    const xmlChar *href;
    xmlXPathCompExprPtr xpExpr;
    xmlXPathObjectPtr result;

    xsltStackElemPtr elem;
    int res;
    void *res_ptr;

    if (ctxt == NULL)
	return(-1);
    if (name == NULL)
	return(0);
    if (value == NULL)
	return(0);

    style = ctxt->style;

#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
	    "Evaluating user parameter %s=%s\n", name, value));
#endif

    /*
     * Name lookup
     */
    href = NULL;

    if (name[0] == '{') {
        int len = 0;

        while ((name[len] != 0) && (name[len] != '}')) len++;
        if (name[len] == 0) {
           xsltTransformError(ctxt, style, NULL,
           "user param : malformed parameter name : %s\n", name);
        } else {
           href = xmlDictLookup(ctxt->dict, &name[1], len-1);
           name = xmlDictLookup(ctxt->dict, &name[len + 1], -1);
       }
    }
    else {
        name = xsltSplitQName(ctxt->dict, name, &prefix);
        if (prefix != NULL) {
            xmlNsPtr ns;

            ns = xmlSearchNs(style->doc, xmlDocGetRootElement(style->doc),
                             prefix);
            if (ns == NULL) {
                xsltTransformError(ctxt, style, NULL,
                "user param : no namespace bound to prefix %s\n", prefix);
                href = NULL;
            } else {
                href = ns->href;
            }
        }
    }

    if (name == NULL)
	return (-1);

    res_ptr = xmlHashLookup2(ctxt->globalVars, name, href);
    if (res_ptr != 0) {
	xsltTransformError(ctxt, style, NULL,
	    "Global parameter %s already defined\n", name);
    }
    if (ctxt->globalVars == NULL)
	ctxt->globalVars = xmlHashCreate(20);

    /*
     * do not overwrite variables with parameters from the command line
     */
    while (style != NULL) {
        elem = ctxt->style->variables;
	while (elem != NULL) {
	    if ((elem->comp != NULL) &&
	        (elem->comp->type == XSLT_FUNC_VARIABLE) &&
		(xmlStrEqual(elem->name, name)) &&
		(xmlStrEqual(elem->nameURI, href))) {
		return(0);
	    }
            elem = elem->next;
	}
        style = xsltNextImport(style);
    }
    style = ctxt->style;
    elem = NULL;

    /*
     * Do the evaluation if @eval is non-zero.
     */

    result = NULL;
    if (eval != 0) {
        xpExpr = xmlXPathCompile(value);
	if (xpExpr != NULL) {
	    xmlDocPtr oldXPDoc;
	    xmlNodePtr oldXPContextNode;
	    int oldXPProximityPosition, oldXPContextSize, oldXPNsNr;
	    xmlNsPtr *oldXPNamespaces;
	    xmlXPathContextPtr xpctxt = ctxt->xpathCtxt;

	    /*
	    * Save context states.
	    */
	    oldXPDoc = xpctxt->doc;
	    oldXPContextNode = xpctxt->node;
	    oldXPProximityPosition = xpctxt->proximityPosition;
	    oldXPContextSize = xpctxt->contextSize;
	    oldXPNamespaces = xpctxt->namespaces;
	    oldXPNsNr = xpctxt->nsNr;

	    /*
	    * SPEC XSLT 1.0:
	    * "At top-level, the expression or template specifying the
	    *  variable value is evaluated with the same context as that used
	    *  to process the root node of the source document: the current
	    *  node is the root node of the source document and the current
	    *  node list is a list containing just the root node of the source
	    *  document."
	    */
	    xpctxt->doc = ctxt->initialContextDoc;
	    xpctxt->node = ctxt->initialContextNode;
	    xpctxt->contextSize = 1;
	    xpctxt->proximityPosition = 1;
	    /*
	    * There is really no in scope namespace for parameters on the
	    * command line.
	    */
	    xpctxt->namespaces = NULL;
	    xpctxt->nsNr = 0;

	    result = xmlXPathCompiledEval(xpExpr, xpctxt);

	    /*
	    * Restore Context states.
	    */
	    xpctxt->doc = oldXPDoc;
	    xpctxt->node = oldXPContextNode;
	    xpctxt->contextSize = oldXPContextSize;
	    xpctxt->proximityPosition = oldXPProximityPosition;
	    xpctxt->namespaces = oldXPNamespaces;
	    xpctxt->nsNr = oldXPNsNr;

	    xmlXPathFreeCompExpr(xpExpr);
	}
	if (result == NULL) {
	    xsltTransformError(ctxt, style, NULL,
		"Evaluating user parameter %s failed\n", name);
	    ctxt->state = XSLT_STATE_STOPPED;
	    return(-1);
	}
    }

    /*
     * If @eval is 0 then @value is to be taken literally and result is NULL
     *
     * If @eval is not 0, then @value is an XPath expression and has been
     * successfully evaluated and result contains the resulting value and
     * is not NULL.
     *
     * Now create an xsltStackElemPtr for insertion into the context's
     * global variable/parameter hash table.
     */

#ifdef WITH_XSLT_DEBUG_VARIABLE
#ifdef LIBXML_DEBUG_ENABLED
    if ((xsltGenericDebugContext == stdout) ||
        (xsltGenericDebugContext == stderr))
	    xmlXPathDebugDumpObject((FILE *)xsltGenericDebugContext,
				    result, 0);
#endif
#endif

    elem = xsltNewStackElem(NULL);
    if (elem != NULL) {
	elem->name = name;
	elem->select = xmlDictLookup(ctxt->dict, value, -1);
	if (href != NULL)
	    elem->nameURI = xmlDictLookup(ctxt->dict, href, -1);
	elem->tree = NULL;
	elem->computed = 1;
	if (eval == 0) {
	    elem->value = xmlXPathNewString(value);
	}
	else {
	    elem->value = result;
	}
    }

    /*
     * Global parameters are stored in the XPath context variables pool.
     */

    res = xmlHashAddEntry2(ctxt->globalVars, name, href, elem);
    if (res != 0) {
	xsltFreeStackElem(elem);
	xsltTransformError(ctxt, style, NULL,
	    "Global parameter %s already defined\n", name);
    }
    return(0);
}