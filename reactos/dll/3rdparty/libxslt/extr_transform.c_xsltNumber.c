#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltStyleItemNumberPtr ;
typedef  int /*<<< orphan*/  xsltElemPreCompPtr ;
typedef  TYPE_4__* xmlXPathContextPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  TYPE_5__* xmlNodePtr ;
struct TYPE_19__ {TYPE_5__* node; int /*<<< orphan*/  doc; } ;
struct TYPE_18__ {int /*<<< orphan*/  doc; } ;
struct TYPE_17__ {int nsNr; int /*<<< orphan*/ * namespaces; } ;
struct TYPE_16__ {int nsNr; TYPE_9__ numdata; int /*<<< orphan*/ * nsList; TYPE_1__* inScopeNs; } ;
struct TYPE_15__ {TYPE_4__* xpathCtxt; } ;
struct TYPE_14__ {int xpathNumber; int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsltNumberFormat (TYPE_2__*,TYPE_9__*,TYPE_5__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*,char*) ; 

void
xsltNumber(xsltTransformContextPtr ctxt, xmlNodePtr node,
	   xmlNodePtr inst, xsltElemPreCompPtr castedComp)
{
#ifdef XSLT_REFACTORED
    xsltStyleItemNumberPtr comp = (xsltStyleItemNumberPtr) castedComp;
#else
    xsltStylePreCompPtr comp = (xsltStylePreCompPtr) castedComp;
#endif
    xmlXPathContextPtr xpctxt;
    xmlNsPtr *oldXPNamespaces;
    int oldXPNsNr;

    if (comp == NULL) {
	xsltTransformError(ctxt, NULL, inst,
	     "xsl:number : compilation failed\n");
	return;
    }

    if ((ctxt == NULL) || (node == NULL) || (inst == NULL) || (comp == NULL))
	return;

    comp->numdata.doc = inst->doc;
    comp->numdata.node = inst;

    xpctxt = ctxt->xpathCtxt;
    oldXPNsNr = xpctxt->nsNr;
    oldXPNamespaces = xpctxt->namespaces;

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

    xsltNumberFormat(ctxt, &comp->numdata, node);

    xpctxt->nsNr = oldXPNsNr;
    xpctxt->namespaces = oldXPNamespaces;
}