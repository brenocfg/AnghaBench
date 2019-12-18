#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_6__ {int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/ * xmlDictLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlStrchr (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * xsltGetNsProp (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

const xmlChar *
xsltEvalStaticAttrValueTemplate(xsltStylesheetPtr style, xmlNodePtr inst,
			const xmlChar *name, const xmlChar *ns, int *found) {
    const xmlChar *ret;
    xmlChar *expr;

    if ((style == NULL) || (inst == NULL) || (name == NULL) ||
        (inst->type != XML_ELEMENT_NODE))
	return(NULL);

    expr = xsltGetNsProp(inst, name, ns);
    if (expr == NULL) {
	*found = 0;
	return(NULL);
    }
    *found = 1;

    ret = xmlStrchr(expr, '{');
    if (ret != NULL) {
	xmlFree(expr);
	return(NULL);
    }
    ret = xmlDictLookup(style->dict, expr, -1);
    xmlFree(expr);
    return(ret);
}