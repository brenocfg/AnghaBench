#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltStylePreCompPtr ;
typedef  TYPE_3__* xsltStyleBasicItemVariablePtr ;
typedef  TYPE_5__* xsltStackElemPtr ;
typedef  TYPE_6__* xmlXPathObjectPtr ;
typedef  TYPE_7__* xmlXPathContextPtr ;
typedef  int /*<<< orphan*/ * xmlXPathCompExprPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  void* xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  const xmlChar ;
struct TYPE_29__ {int proximityPosition; int contextSize; int nsNr; int /*<<< orphan*/ * doc; int /*<<< orphan*/ * namespaces; void* node; } ;
struct TYPE_28__ {scalar_t__ boolval; } ;
struct TYPE_27__ {int computed; TYPE_6__* value; int /*<<< orphan*/  const* name; int /*<<< orphan*/ * tree; int /*<<< orphan*/ * select; TYPE_3__* comp; } ;
struct TYPE_26__ {int nsNr; int /*<<< orphan*/ * inst; int /*<<< orphan*/ * comp; int /*<<< orphan*/ * nsList; TYPE_1__* inScopeNs; } ;
struct TYPE_25__ {scalar_t__ debugStatus; int /*<<< orphan*/ * inst; int /*<<< orphan*/ * output; void* insert; TYPE_7__* xpathCtxt; int /*<<< orphan*/  node; int /*<<< orphan*/ * initialContextDoc; int /*<<< orphan*/  state; void* initialContextNode; } ;
struct TYPE_24__ {int xpathNumber; int /*<<< orphan*/ * list; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ XSLT_DEBUG_NONE ; 
 int /*<<< orphan*/  XSLT_RVT_GLOBAL ; 
 int /*<<< orphan*/  XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  XSLT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 
 int /*<<< orphan*/ * xmlXPathCompile (int /*<<< orphan*/ *) ; 
 TYPE_6__* xmlXPathCompiledEval (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  xmlXPathDebugDumpObject (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlXPathFreeCompExpr (int /*<<< orphan*/ *) ; 
 TYPE_6__* xmlXPathNewCString (char*) ; 
 TYPE_6__* xmlXPathNewValueTree (void*) ; 
 int /*<<< orphan*/  xslHandleDebugger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltApplyOneTemplate (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* xsltComputingGlobalVarMarker ; 
 int /*<<< orphan*/ * xsltCreateRVT (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltFlagRVTs (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltGenericDebug (scalar_t__,char*,int /*<<< orphan*/  const*) ; 
 scalar_t__ xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltRegisterPersistRVT (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static xmlXPathObjectPtr
xsltEvalGlobalVariable(xsltStackElemPtr elem, xsltTransformContextPtr ctxt)
{
    xmlXPathObjectPtr result = NULL;
    xmlNodePtr oldInst;
    const xmlChar* oldVarName;

#ifdef XSLT_REFACTORED
    xsltStyleBasicItemVariablePtr comp;
#else
    xsltStylePreCompPtr comp;
#endif

    if ((ctxt == NULL) || (elem == NULL))
	return(NULL);
    if (elem->computed)
	return(elem->value);


#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
	"Evaluating global variable %s\n", elem->name));
#endif

#ifdef WITH_DEBUGGER
    if ((ctxt->debugStatus != XSLT_DEBUG_NONE) &&
        elem->comp && elem->comp->inst)
        xslHandleDebugger(elem->comp->inst, NULL, NULL, ctxt);
#endif

    oldInst = ctxt->inst;
#ifdef XSLT_REFACTORED
    comp = (xsltStyleBasicItemVariablePtr) elem->comp;
#else
    comp = elem->comp;
#endif
    oldVarName = elem->name;
    elem->name = xsltComputingGlobalVarMarker;
    /*
    * OPTIMIZE TODO: We should consider instantiating global vars/params
    *  on-demand. The vars/params don't need to be evaluated if never
    *  called; and in the case of global params, if values for such params
    *  are provided by the user.
    */
    if (elem->select != NULL) {
	xmlXPathCompExprPtr xpExpr = NULL;
	xmlDocPtr oldXPDoc;
	xmlNodePtr oldXPContextNode;
	int oldXPProximityPosition, oldXPContextSize, oldXPNsNr;
	xmlNsPtr *oldXPNamespaces;
	xmlXPathContextPtr xpctxt = ctxt->xpathCtxt;

	if ((comp != NULL) && (comp->comp != NULL)) {
	    xpExpr = comp->comp;
	} else {
	    xpExpr = xmlXPathCompile(elem->select);
	}
	if (xpExpr == NULL)
	    goto error;


	if (comp != NULL)
	    ctxt->inst = comp->inst;
	else
	    ctxt->inst = NULL;
	/*
	* SPEC XSLT 1.0:
	* "At top-level, the expression or template specifying the
	*  variable value is evaluated with the same context as that used
	*  to process the root node of the source document: the current
	*  node is the root node of the source document and the current
	*  node list is a list containing just the root node of the source
	*  document."
	*/
	/*
	* Save context states.
	*/
	oldXPDoc = xpctxt->doc;
	oldXPContextNode = xpctxt->node;
	oldXPProximityPosition = xpctxt->proximityPosition;
	oldXPContextSize = xpctxt->contextSize;
	oldXPNamespaces = xpctxt->namespaces;
	oldXPNsNr = xpctxt->nsNr;

	xpctxt->node = ctxt->initialContextNode;
	xpctxt->doc = ctxt->initialContextDoc;
	xpctxt->contextSize = 1;
	xpctxt->proximityPosition = 1;

	if (comp != NULL) {

#ifdef XSLT_REFACTORED
	    if (comp->inScopeNs != NULL) {
		xpctxt->namespaces = comp->inScopeNs->list;
		xpctxt->nsNr = comp->inScopeNs->xpathNumber;
	    } else {
		xpctxt->namespaces = NULL;
		xpctxt->nsNr = 0;
	    }
#else
	    xpctxt->namespaces = comp->nsList;
	    xpctxt->nsNr = comp->nsNr;
#endif
	} else {
	    xpctxt->namespaces = NULL;
	    xpctxt->nsNr = 0;
	}

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

	if ((comp == NULL) || (comp->comp == NULL))
	    xmlXPathFreeCompExpr(xpExpr);
	if (result == NULL) {
	    if (comp == NULL)
		xsltTransformError(ctxt, NULL, NULL,
		    "Evaluating global variable %s failed\n", elem->name);
	    else
		xsltTransformError(ctxt, NULL, comp->inst,
		    "Evaluating global variable %s failed\n", elem->name);
	    ctxt->state = XSLT_STATE_STOPPED;
            goto error;
        }

        /*
         * Mark all RVTs that are referenced from result as part
         * of this variable so they won't be freed too early.
         */
        xsltFlagRVTs(ctxt, result, XSLT_RVT_GLOBAL);

#ifdef WITH_XSLT_DEBUG_VARIABLE
#ifdef LIBXML_DEBUG_ENABLED
	if ((xsltGenericDebugContext == stdout) ||
	    (xsltGenericDebugContext == stderr))
	    xmlXPathDebugDumpObject((FILE *)xsltGenericDebugContext,
				    result, 0);
#endif
#endif
    } else {
	if (elem->tree == NULL) {
	    result = xmlXPathNewCString("");
	} else {
	    xmlDocPtr container;
	    xmlNodePtr oldInsert;
	    xmlDocPtr  oldOutput, oldXPDoc;
	    /*
	    * Generate a result tree fragment.
	    */
	    container = xsltCreateRVT(ctxt);
	    if (container == NULL)
		goto error;
	    /*
	    * Let the lifetime of the tree fragment be handled by
	    * the Libxslt's garbage collector.
	    */
	    xsltRegisterPersistRVT(ctxt, container);

	    oldOutput = ctxt->output;
	    oldInsert = ctxt->insert;

	    oldXPDoc = ctxt->xpathCtxt->doc;

	    ctxt->output = container;
	    ctxt->insert = (xmlNodePtr) container;

	    ctxt->xpathCtxt->doc = ctxt->initialContextDoc;
	    /*
	    * Process the sequence constructor.
	    */
	    xsltApplyOneTemplate(ctxt, ctxt->node, elem->tree, NULL, NULL);

	    ctxt->xpathCtxt->doc = oldXPDoc;

	    ctxt->insert = oldInsert;
	    ctxt->output = oldOutput;

	    result = xmlXPathNewValueTree((xmlNodePtr) container);
	    if (result == NULL) {
		result = xmlXPathNewCString("");
	    } else {
	        result->boolval = 0; /* Freeing is not handled there anymore */
	    }
#ifdef WITH_XSLT_DEBUG_VARIABLE
#ifdef LIBXML_DEBUG_ENABLED
	    if ((xsltGenericDebugContext == stdout) ||
		(xsltGenericDebugContext == stderr))
		xmlXPathDebugDumpObject((FILE *)xsltGenericDebugContext,
					result, 0);
#endif
#endif
	}
    }

error:
    elem->name = oldVarName;
    ctxt->inst = oldInst;
    if (result != NULL) {
	elem->value = result;
	elem->computed = 1;
    }
    return(result);
}