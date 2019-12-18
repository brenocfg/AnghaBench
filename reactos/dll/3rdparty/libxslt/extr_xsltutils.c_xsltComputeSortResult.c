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
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltStyleItemSortPtr ;
typedef  scalar_t__ xsltLocale ;
typedef  TYPE_4__* xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  TYPE_5__* xmlNodeSetPtr ;
typedef  TYPE_6__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_23__ {TYPE_3__* psvi; } ;
struct TYPE_22__ {int nodeNr; TYPE_6__** nodeTab; } ;
struct TYPE_21__ {scalar_t__ type; int index; int /*<<< orphan*/ * stringval; } ;
struct TYPE_20__ {int nsNr; scalar_t__ locale; scalar_t__ number; int /*<<< orphan*/ * comp; int /*<<< orphan*/ * nsList; TYPE_1__* inScopeNs; int /*<<< orphan*/ * select; } ;
struct TYPE_19__ {TYPE_15__* xpathCtxt; TYPE_6__* inst; TYPE_6__* node; int /*<<< orphan*/  state; TYPE_5__* nodeList; } ;
struct TYPE_18__ {int xpathNumber; int /*<<< orphan*/ * list; } ;
struct TYPE_17__ {int proximityPosition; int contextSize; int nsNr; int /*<<< orphan*/ * namespaces; TYPE_6__* node; } ;

/* Variables and functions */
 scalar_t__ XPATH_NUMBER ; 
 scalar_t__ XPATH_STRING ; 
 int /*<<< orphan*/  XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 TYPE_4__** xmlMalloc (int) ; 
 TYPE_4__* xmlXPathCompiledEval (int /*<<< orphan*/ *,TYPE_15__*) ; 
 TYPE_4__* xmlXPathConvertNumber (TYPE_4__*) ; 
 TYPE_4__* xmlXPathConvertString (TYPE_4__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericErrorContext ; 
 scalar_t__ xsltStrxfrm (scalar_t__,int /*<<< orphan*/ *) ; 

xmlXPathObjectPtr *
xsltComputeSortResult(xsltTransformContextPtr ctxt, xmlNodePtr sort) {
#ifdef XSLT_REFACTORED
    xsltStyleItemSortPtr comp;
#else
    xsltStylePreCompPtr comp;
#endif
    xmlXPathObjectPtr *results = NULL;
    xmlNodeSetPtr list = NULL;
    xmlXPathObjectPtr res;
    int len = 0;
    int i;
    xmlNodePtr oldNode;
    xmlNodePtr oldInst;
    int	oldPos, oldSize ;
    int oldNsNr;
    xmlNsPtr *oldNamespaces;

    comp = sort->psvi;
    if (comp == NULL) {
	xsltGenericError(xsltGenericErrorContext,
	     "xsl:sort : compilation failed\n");
	return(NULL);
    }

    if ((comp->select == NULL) || (comp->comp == NULL))
	return(NULL);

    list = ctxt->nodeList;
    if ((list == NULL) || (list->nodeNr <= 1))
	return(NULL);

    len = list->nodeNr;

    /* TODO: xsl:sort lang attribute */
    /* TODO: xsl:sort case-order attribute */


    results = xmlMalloc(len * sizeof(xmlXPathObjectPtr));
    if (results == NULL) {
	xsltGenericError(xsltGenericErrorContext,
	     "xsltComputeSortResult: memory allocation failure\n");
	return(NULL);
    }

    oldNode = ctxt->node;
    oldInst = ctxt->inst;
    oldPos = ctxt->xpathCtxt->proximityPosition;
    oldSize = ctxt->xpathCtxt->contextSize;
    oldNsNr = ctxt->xpathCtxt->nsNr;
    oldNamespaces = ctxt->xpathCtxt->namespaces;
    for (i = 0;i < len;i++) {
	ctxt->inst = sort;
	ctxt->xpathCtxt->contextSize = len;
	ctxt->xpathCtxt->proximityPosition = i + 1;
	ctxt->node = list->nodeTab[i];
	ctxt->xpathCtxt->node = ctxt->node;
#ifdef XSLT_REFACTORED
	if (comp->inScopeNs != NULL) {
	    ctxt->xpathCtxt->namespaces = comp->inScopeNs->list;
	    ctxt->xpathCtxt->nsNr = comp->inScopeNs->xpathNumber;
	} else {
	    ctxt->xpathCtxt->namespaces = NULL;
	    ctxt->xpathCtxt->nsNr = 0;
	}
#else
	ctxt->xpathCtxt->namespaces = comp->nsList;
	ctxt->xpathCtxt->nsNr = comp->nsNr;
#endif
	res = xmlXPathCompiledEval(comp->comp, ctxt->xpathCtxt);
	if (res != NULL) {
	    if (res->type != XPATH_STRING)
		res = xmlXPathConvertString(res);
	    if (comp->number)
		res = xmlXPathConvertNumber(res);
	    res->index = i;	/* Save original pos for dupl resolv */
	    if (comp->number) {
		if (res->type == XPATH_NUMBER) {
		    results[i] = res;
		} else {
#ifdef WITH_XSLT_DEBUG_PROCESS
		    xsltGenericDebug(xsltGenericDebugContext,
			"xsltComputeSortResult: select didn't evaluate to a number\n");
#endif
		    results[i] = NULL;
		}
	    } else {
		if (res->type == XPATH_STRING) {
		    if (comp->locale != (xsltLocale)0) {
			xmlChar *str = res->stringval;
			res->stringval = (xmlChar *) xsltStrxfrm(comp->locale, str);
			xmlFree(str);
		    }

		    results[i] = res;
		} else {
#ifdef WITH_XSLT_DEBUG_PROCESS
		    xsltGenericDebug(xsltGenericDebugContext,
			"xsltComputeSortResult: select didn't evaluate to a string\n");
#endif
		    results[i] = NULL;
		}
	    }
	} else {
	    ctxt->state = XSLT_STATE_STOPPED;
	    results[i] = NULL;
	}
    }
    ctxt->node = oldNode;
    ctxt->inst = oldInst;
    ctxt->xpathCtxt->contextSize = oldSize;
    ctxt->xpathCtxt->proximityPosition = oldPos;
    ctxt->xpathCtxt->nsNr = oldNsNr;
    ctxt->xpathCtxt->namespaces = oldNamespaces;

    return(results);
}