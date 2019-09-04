#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltElemPreCompPtr ;
typedef  TYPE_3__* xmlXPathContextPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  TYPE_4__* xmlNodePtr ;
struct TYPE_17__ {TYPE_4__* node; int /*<<< orphan*/  doc; } ;
struct TYPE_16__ {int /*<<< orphan*/  doc; } ;
struct TYPE_15__ {int nsNr; int /*<<< orphan*/ * namespaces; } ;
struct TYPE_14__ {int nsNr; TYPE_8__ numdata; int /*<<< orphan*/ * nsList; } ;
struct TYPE_13__ {TYPE_3__* xpathCtxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsltNumberFormat (TYPE_1__*,TYPE_8__*,TYPE_4__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,TYPE_4__*,char*) ; 

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