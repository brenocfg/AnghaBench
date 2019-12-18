#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/  xmlXPathCompExprPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  void* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_13__ {int proximityPosition; int contextSize; int nsNr; int /*<<< orphan*/ * namespaces; void* node; } ;
struct TYPE_12__ {scalar_t__ type; int /*<<< orphan*/ * stringval; } ;
struct TYPE_11__ {TYPE_9__* xpathCtxt; void* node; int /*<<< orphan*/ * inst; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ XPATH_STRING ; 
 int /*<<< orphan*/  XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  XSLT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_TEMPLATES ; 
 TYPE_2__* xmlXPathCompiledEval (int /*<<< orphan*/ ,TYPE_9__*) ; 
 TYPE_2__* xmlXPathConvertString (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

xmlChar *
xsltEvalXPathStringNs(xsltTransformContextPtr ctxt, xmlXPathCompExprPtr comp,
	              int nsNr, xmlNsPtr *nsList) {
    xmlChar *ret = NULL;
    xmlXPathObjectPtr res;
    xmlNodePtr oldInst;
    xmlNodePtr oldNode;
    int	oldPos, oldSize;
    int oldNsNr;
    xmlNsPtr *oldNamespaces;

    if ((ctxt == NULL) || (ctxt->inst == NULL)) {
        xsltTransformError(ctxt, NULL, NULL,
            "xsltEvalXPathStringNs: No context or instruction\n");
        return(0);
    }

    oldInst = ctxt->inst;
    oldNode = ctxt->node;
    oldPos = ctxt->xpathCtxt->proximityPosition;
    oldSize = ctxt->xpathCtxt->contextSize;
    oldNsNr = ctxt->xpathCtxt->nsNr;
    oldNamespaces = ctxt->xpathCtxt->namespaces;

    ctxt->xpathCtxt->node = ctxt->node;
    /* TODO: do we need to propagate the namespaces here ? */
    ctxt->xpathCtxt->namespaces = nsList;
    ctxt->xpathCtxt->nsNr = nsNr;
    res = xmlXPathCompiledEval(comp, ctxt->xpathCtxt);
    if (res != NULL) {
	if (res->type != XPATH_STRING)
	    res = xmlXPathConvertString(res);
	if (res->type == XPATH_STRING) {
            ret = res->stringval;
	    res->stringval = NULL;
	} else {
	    xsltTransformError(ctxt, NULL, NULL,
		 "xpath : string() function didn't return a String\n");
	}
	xmlXPathFreeObject(res);
    } else {
	ctxt->state = XSLT_STATE_STOPPED;
    }
#ifdef WITH_XSLT_DEBUG_TEMPLATES
    XSLT_TRACE(ctxt,XSLT_TRACE_TEMPLATES,xsltGenericDebug(xsltGenericDebugContext,
	 "xsltEvalXPathString: returns %s\n", ret));
#endif
    ctxt->inst = oldInst;
    ctxt->node = oldNode;
    ctxt->xpathCtxt->contextSize = oldSize;
    ctxt->xpathCtxt->proximityPosition = oldPos;
    ctxt->xpathCtxt->nsNr = oldNsNr;
    ctxt->xpathCtxt->namespaces = oldNamespaces;
    return(ret);
}