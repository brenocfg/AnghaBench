#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xsltTransformContextPtr ;
typedef  TYPE_4__* xmlXPathObjectPtr ;
typedef  TYPE_5__* xmlNsPtr ;
typedef  TYPE_6__* xmlNodePtr ;
typedef  TYPE_7__* xmlDocPtr ;
struct TYPE_19__ {char* name; void* psvi; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_7__* doc; } ;
struct TYPE_17__ {TYPE_2__* next; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_1__* nodesetval; } ;
struct TYPE_15__ {int /*<<< orphan*/  inst; } ;
struct TYPE_14__ {scalar_t__ type; } ;
struct TYPE_13__ {int nodeNr; TYPE_6__** nodeTab; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 scalar_t__ XPATH_NODESET ; 
 scalar_t__ XPATH_XSLT_TREE ; 
 void* XSLT_RVT_FUNC_RESULT ; 
 void* XSLT_RVT_GLOBAL ; 
 void* XSLT_RVT_LOCAL ; 
 int /*<<< orphan*/  XSLT_TRACE (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_VARIABLES ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,TYPE_7__*,void*,void*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
xsltFlagRVTs(xsltTransformContextPtr ctxt, xmlXPathObjectPtr obj, void *val) {
    int i;
    xmlNodePtr cur;
    xmlDocPtr doc;

    if ((ctxt == NULL) || (obj == NULL))
	return(-1);

    /*
    * OPTIMIZE TODO: If no local variables/params and no local tree
    * fragments were created, then we don't need to analyse the XPath
    * objects for tree fragments.
    */

    if ((obj->type != XPATH_NODESET) && (obj->type != XPATH_XSLT_TREE))
	return(0);
    if ((obj->nodesetval == NULL) || (obj->nodesetval->nodeNr == 0))
	return(0);

    for (i = 0; i < obj->nodesetval->nodeNr; i++) {
	cur = obj->nodesetval->nodeTab[i];
	if (cur->type == XML_NAMESPACE_DECL) {
	    /*
	    * The XPath module sets the owner element of a ns-node on
	    * the ns->next field.
	    */
	    if ((((xmlNsPtr) cur)->next != NULL) &&
		(((xmlNsPtr) cur)->next->type == XML_ELEMENT_NODE))
	    {
		cur = (xmlNodePtr) ((xmlNsPtr) cur)->next;
		doc = cur->doc;
	    } else {
		xsltTransformError(ctxt, NULL, ctxt->inst,
		    "Internal error in xsltFlagRVTs(): "
		    "Cannot retrieve the doc of a namespace node.\n");
		return(-1);
	    }
	} else {
	    doc = cur->doc;
	}
	if (doc == NULL) {
	    xsltTransformError(ctxt, NULL, ctxt->inst,
		"Internal error in xsltFlagRVTs(): "
		"Cannot retrieve the doc of a node.\n");
	    return(-1);
	}
	if (doc->name && (doc->name[0] == ' ') &&
            doc->psvi != XSLT_RVT_GLOBAL) {
	    /*
	    * This is a result tree fragment.
	    * We store ownership information in the @psvi field.
	    * TODO: How do we know if this is a doc acquired via the
	    *  document() function?
	    */
#ifdef WITH_XSLT_DEBUG_VARIABLE
            XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
                "Flagging RVT %p: %p -> %p\n", doc, doc->psvi, val));
#endif

            if (val == XSLT_RVT_LOCAL) {
                if (doc->psvi == XSLT_RVT_FUNC_RESULT)
                    doc->psvi = XSLT_RVT_LOCAL;
            } else if (val == XSLT_RVT_GLOBAL) {
                if (doc->psvi != XSLT_RVT_LOCAL) {
		    xmlGenericError(xmlGenericErrorContext,
                            "xsltFlagRVTs: Invalid transition %p => GLOBAL\n",
                            doc->psvi);
                    doc->psvi = XSLT_RVT_GLOBAL;
                    return(-1);
                }

                /* Will be registered as persistant in xsltReleaseLocalRVTs. */
                doc->psvi = XSLT_RVT_GLOBAL;
            } else if (val == XSLT_RVT_FUNC_RESULT) {
	        doc->psvi = val;
            }
	}
    }

    return(0);
}