#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltTransformContextPtr ;
typedef  TYPE_1__* xsltAttrVTPtr ;
typedef  scalar_t__ xmlXPathCompExprPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
typedef  int /*<<< orphan*/  const xmlChar ;
struct TYPE_2__ {int strstart; int nb_seg; int /*<<< orphan*/  nsList; int /*<<< orphan*/  nsNr; scalar_t__* segments; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* xmlStrcat (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* xsltEvalXPathStringNs (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

xmlChar *
xsltEvalAVT(xsltTransformContextPtr ctxt, void *avt, xmlNodePtr node) {
    xmlChar *ret = NULL, *tmp;
    xmlXPathCompExprPtr comp;
    xsltAttrVTPtr cur = (xsltAttrVTPtr) avt;
    int i;
    int str;

    if ((ctxt == NULL) || (avt == NULL) || (node == NULL))
        return(NULL);
    str = cur->strstart;
    for (i = 0;i < cur->nb_seg;i++) {
        if (str) {
	    ret = xmlStrcat(ret, (const xmlChar *) cur->segments[i]);
	} else {
	    comp = (xmlXPathCompExprPtr) cur->segments[i];
	    tmp = xsltEvalXPathStringNs(ctxt, comp, cur->nsNr, cur->nsList);
	    if (tmp != NULL) {
	        if (ret != NULL) {
		    ret = xmlStrcat(ret, tmp);
		    xmlFree(tmp);
		} else {
		    ret = tmp;
		}
	    }
	}
	str = !str;
    }
    return(ret);
}