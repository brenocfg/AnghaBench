#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  int /*<<< orphan*/ * xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/  xmlXPathCompExprPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
struct TYPE_8__ {int contextSize; int proximityPosition; int nsNr; int /*<<< orphan*/ * namespaces; int /*<<< orphan*/  node; } ;
struct TYPE_7__ {TYPE_4__* xpathCtxt; int /*<<< orphan*/ * inst; int /*<<< orphan*/  state; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  XSLT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_TEMPLATES ; 
 int /*<<< orphan*/ * xmlXPathCompiledEval (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int xmlXPathEvalPredicate (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int
xsltEvalXPathPredicate(xsltTransformContextPtr ctxt, xmlXPathCompExprPtr comp,
		       xmlNsPtr *nsList, int nsNr) {
    int ret;
    xmlXPathObjectPtr res;
    int oldNsNr;
    xmlNsPtr *oldNamespaces;
    xmlNodePtr oldInst;
    int oldProximityPosition, oldContextSize;

    if ((ctxt == NULL) || (ctxt->inst == NULL)) {
        xsltTransformError(ctxt, NULL, NULL,
            "xsltEvalXPathPredicate: No context or instruction\n");
        return(0);
    }

    oldContextSize = ctxt->xpathCtxt->contextSize;
    oldProximityPosition = ctxt->xpathCtxt->proximityPosition;
    oldNsNr = ctxt->xpathCtxt->nsNr;
    oldNamespaces = ctxt->xpathCtxt->namespaces;
    oldInst = ctxt->inst;

    ctxt->xpathCtxt->node = ctxt->node;
    ctxt->xpathCtxt->namespaces = nsList;
    ctxt->xpathCtxt->nsNr = nsNr;

    res = xmlXPathCompiledEval(comp, ctxt->xpathCtxt);

    if (res != NULL) {
	ret = xmlXPathEvalPredicate(ctxt->xpathCtxt, res);
	xmlXPathFreeObject(res);
#ifdef WITH_XSLT_DEBUG_TEMPLATES
	XSLT_TRACE(ctxt,XSLT_TRACE_TEMPLATES,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltEvalXPathPredicate: returns %d\n", ret));
#endif
    } else {
#ifdef WITH_XSLT_DEBUG_TEMPLATES
	XSLT_TRACE(ctxt,XSLT_TRACE_TEMPLATES,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltEvalXPathPredicate: failed\n"));
#endif
	ctxt->state = XSLT_STATE_STOPPED;
	ret = 0;
    }
    ctxt->xpathCtxt->nsNr = oldNsNr;

    ctxt->xpathCtxt->namespaces = oldNamespaces;
    ctxt->inst = oldInst;
    ctxt->xpathCtxt->contextSize = oldContextSize;
    ctxt->xpathCtxt->proximityPosition = oldProximityPosition;

    return(ret);
}