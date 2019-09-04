#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  int /*<<< orphan*/ * xsltTemplatePtr ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltElemPreCompPtr ;
typedef  int /*<<< orphan*/  xsltDocumentPtr ;
typedef  TYPE_3__* xmlXPathObjectPtr ;
typedef  TYPE_4__* xmlXPathContextPtr ;
typedef  TYPE_5__* xmlNodeSetPtr ;
typedef  TYPE_6__* xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
struct TYPE_29__ {scalar_t__ type; int /*<<< orphan*/ * doc; struct TYPE_29__* next; struct TYPE_29__* children; } ;
struct TYPE_28__ {int nodeNr; TYPE_6__** nodeTab; } ;
struct TYPE_27__ {int proximityPosition; int contextSize; int /*<<< orphan*/ * doc; } ;
struct TYPE_26__ {scalar_t__ type; TYPE_5__* nodesetval; } ;
struct TYPE_25__ {int /*<<< orphan*/ * comp; int /*<<< orphan*/ * select; } ;
struct TYPE_24__ {int /*<<< orphan*/ * currentTemplateRule; TYPE_6__* node; TYPE_5__* nodeList; int /*<<< orphan*/  document; int /*<<< orphan*/  state; TYPE_4__* xpathCtxt; } ;

/* Variables and functions */
 scalar_t__ IS_XSLT_ELEM (TYPE_6__*) ; 
 scalar_t__ IS_XSLT_NAME (TYPE_6__*,char*) ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 scalar_t__ XPATH_NODESET ; 
 int XSLT_MAX_SORT ; 
 int /*<<< orphan*/  XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_3__*) ; 
 int /*<<< orphan*/  xsltApplySequenceConstructor (TYPE_1__*,TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltDoSortFunction (TYPE_1__*,TYPE_6__**,int) ; 
 int /*<<< orphan*/  xsltGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericErrorContext ; 
 TYPE_3__* xsltPreCompEval (TYPE_1__*,TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,TYPE_6__*,char*,...) ; 

void
xsltForEach(xsltTransformContextPtr ctxt, xmlNodePtr contextNode,
	    xmlNodePtr inst, xsltElemPreCompPtr castedComp)
{
#ifdef XSLT_REFACTORED
    xsltStyleItemForEachPtr comp = (xsltStyleItemForEachPtr) castedComp;
#else
    xsltStylePreCompPtr comp = (xsltStylePreCompPtr) castedComp;
#endif
    int i;
    xmlXPathObjectPtr res = NULL;
    xmlNodePtr cur, curInst;
    xmlNodeSetPtr list = NULL;
    xmlNodeSetPtr oldList;
    int oldXPProximityPosition, oldXPContextSize;
    xmlNodePtr oldContextNode;
    xsltTemplatePtr oldCurTemplRule;
    xmlDocPtr oldXPDoc;
    xsltDocumentPtr oldDocInfo;
    xmlXPathContextPtr xpctxt;

    if ((ctxt == NULL) || (contextNode == NULL) || (inst == NULL)) {
	xsltGenericError(xsltGenericErrorContext,
	    "xsltForEach(): Bad arguments.\n");
	return;
    }

    if (comp == NULL) {
        xsltTransformError(ctxt, NULL, inst,
	    "Internal error in xsltForEach(): "
	    "The XSLT 'for-each' instruction was not compiled.\n");
        return;
    }
    if ((comp->select == NULL) || (comp->comp == NULL)) {
	xsltTransformError(ctxt, NULL, inst,
	    "Internal error in xsltForEach(): "
	    "The selecting expression of the XSLT 'for-each' "
	    "instruction was not compiled correctly.\n");
	return;
    }
    xpctxt = ctxt->xpathCtxt;

#ifdef WITH_XSLT_DEBUG_PROCESS
    XSLT_TRACE(ctxt,XSLT_TRACE_FOR_EACH,xsltGenericDebug(xsltGenericDebugContext,
	 "xsltForEach: select %s\n", comp->select));
#endif

    /*
    * Save context states.
    */
    oldDocInfo = ctxt->document;
    oldList = ctxt->nodeList;
    oldContextNode = ctxt->node;
    /*
    * The "current template rule" is cleared for the instantiation of
    * xsl:for-each.
    */
    oldCurTemplRule = ctxt->currentTemplateRule;
    ctxt->currentTemplateRule = NULL;

    oldXPDoc = xpctxt->doc;
    oldXPProximityPosition = xpctxt->proximityPosition;
    oldXPContextSize = xpctxt->contextSize;

    /*
    * Evaluate the 'select' expression.
    */
    res = xsltPreCompEval(ctxt, contextNode, comp);

    if (res != NULL) {
	if (res->type == XPATH_NODESET)
	    list = res->nodesetval;
	else {
	    xsltTransformError(ctxt, NULL, inst,
		"The 'select' expression does not evaluate to a node set.\n");

#ifdef WITH_XSLT_DEBUG_PROCESS
	    XSLT_TRACE(ctxt,XSLT_TRACE_FOR_EACH,xsltGenericDebug(xsltGenericDebugContext,
		"xsltForEach: select didn't evaluate to a node list\n"));
#endif
	    goto error;
	}
    } else {
	xsltTransformError(ctxt, NULL, inst,
	    "Failed to evaluate the 'select' expression.\n");
	ctxt->state = XSLT_STATE_STOPPED;
	goto error;
    }

    if ((list == NULL) || (list->nodeNr <= 0))
	goto exit;

#ifdef WITH_XSLT_DEBUG_PROCESS
    XSLT_TRACE(ctxt,XSLT_TRACE_FOR_EACH,xsltGenericDebug(xsltGenericDebugContext,
	"xsltForEach: select evaluates to %d nodes\n", list->nodeNr));
#endif

    /*
    * Set the list; this has to be done already here for xsltDoSortFunction().
    */
    ctxt->nodeList = list;
    /*
    * Handle xsl:sort instructions and skip them for further processing.
    * BUG TODO: We are not using namespaced potentially defined on the
    * xsl:sort element; XPath expression might fail.
    */
    curInst = inst->children;
    if (IS_XSLT_ELEM(curInst) && IS_XSLT_NAME(curInst, "sort")) {
	int nbsorts = 0;
	xmlNodePtr sorts[XSLT_MAX_SORT];

	sorts[nbsorts++] = curInst;

#ifdef WITH_DEBUGGER
	if (xslDebugStatus != XSLT_DEBUG_NONE)
	    xslHandleDebugger(curInst, contextNode, NULL, ctxt);
#endif

	curInst = curInst->next;
	while (IS_XSLT_ELEM(curInst) && IS_XSLT_NAME(curInst, "sort")) {
	    if (nbsorts >= XSLT_MAX_SORT) {
		xsltTransformError(ctxt, NULL, curInst,
		    "The number of xsl:sort instructions exceeds the "
		    "maximum (%d) allowed by this processor.\n",
		    XSLT_MAX_SORT);
		goto error;
	    } else {
		sorts[nbsorts++] = curInst;
	    }

#ifdef WITH_DEBUGGER
	    if (xslDebugStatus != XSLT_DEBUG_NONE)
		xslHandleDebugger(curInst, contextNode, NULL, ctxt);
#endif
	    curInst = curInst->next;
	}
	xsltDoSortFunction(ctxt, sorts, nbsorts);
    }
    xpctxt->contextSize = list->nodeNr;
    /*
    * Instantiate the sequence constructor for each selected node.
    */
    for (i = 0; i < list->nodeNr; i++) {
	cur = list->nodeTab[i];
	/*
	* The selected node becomes the "current node".
	*/
	ctxt->node = cur;
	/*
	* An xsl:for-each can change the current context doc.
	* OPTIMIZE TODO: Get rid of the need to set the context doc.
	*/
	if ((cur->type != XML_NAMESPACE_DECL) && (cur->doc != NULL))
	    xpctxt->doc = cur->doc;

	xpctxt->proximityPosition = i + 1;

	xsltApplySequenceConstructor(ctxt, cur, curInst, NULL);
    }

exit:
error:
    if (res != NULL)
	xmlXPathFreeObject(res);
    /*
    * Restore old states.
    */
    ctxt->document = oldDocInfo;
    ctxt->nodeList = oldList;
    ctxt->node = oldContextNode;
    ctxt->currentTemplateRule = oldCurTemplRule;

    xpctxt->doc = oldXPDoc;
    xpctxt->contextSize = oldXPContextSize;
    xpctxt->proximityPosition = oldXPProximityPosition;
}