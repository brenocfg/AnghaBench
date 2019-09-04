#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xmlXPathObjectPtr ;
typedef  TYPE_3__* xmlXPathContextPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  void* xmlNodePtr ;
struct TYPE_9__ {int proximityPosition; int contextSize; int nsNr; int /*<<< orphan*/ * namespaces; void* node; } ;
struct TYPE_8__ {int nsNr; int /*<<< orphan*/  comp; int /*<<< orphan*/ * nsList; } ;
struct TYPE_7__ {TYPE_3__* xpathCtxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlXPathCompiledEval (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static xmlXPathObjectPtr
xsltPreCompEval(xsltTransformContextPtr ctxt, xmlNodePtr node,
                xsltStylePreCompPtr comp) {
    xmlXPathObjectPtr res;
    xmlXPathContextPtr xpctxt;
    xmlNodePtr oldXPContextNode;
    xmlNsPtr *oldXPNamespaces;
    int oldXPProximityPosition, oldXPContextSize, oldXPNsNr;

    xpctxt = ctxt->xpathCtxt;
    oldXPContextNode = xpctxt->node;
    oldXPProximityPosition = xpctxt->proximityPosition;
    oldXPContextSize = xpctxt->contextSize;
    oldXPNsNr = xpctxt->nsNr;
    oldXPNamespaces = xpctxt->namespaces;

    xpctxt->node = node;
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

    res = xmlXPathCompiledEval(comp->comp, xpctxt);

    xpctxt->node = oldXPContextNode;
    xpctxt->proximityPosition = oldXPProximityPosition;
    xpctxt->contextSize = oldXPContextSize;
    xpctxt->nsNr = oldXPNsNr;
    xpctxt->namespaces = oldXPNamespaces;

    return(res);
}