#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltStylesheetPtr ;
typedef  TYPE_1__* xsltStylePreCompPtr ;
typedef  TYPE_1__* xsltStyleItemCopyPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__* psvi; } ;
struct TYPE_7__ {int has_use; int /*<<< orphan*/ * use; TYPE_3__* inst; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  XSLT_FUNC_COPY ; 
 int /*<<< orphan*/  XSLT_NAMESPACE ; 
 int /*<<< orphan*/ * xsltGetCNsProp (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* xsltNewStylePreComp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xsltCopyComp(xsltStylesheetPtr style, xmlNodePtr inst) {
#ifdef XSLT_REFACTORED
    xsltStyleItemCopyPtr comp;
#else
    xsltStylePreCompPtr comp;
#endif

    if ((style == NULL) || (inst == NULL) || (inst->type != XML_ELEMENT_NODE))
	return;
#ifdef XSLT_REFACTORED
    comp = (xsltStyleItemCopyPtr) xsltNewStylePreComp(style, XSLT_FUNC_COPY);
#else
    comp = xsltNewStylePreComp(style, XSLT_FUNC_COPY);
#endif

    if (comp == NULL)
	return;
    inst->psvi = comp;
    comp->inst = inst;


    comp->use = xsltGetCNsProp(style, inst, (const xmlChar *)"use-attribute-sets",
				    XSLT_NAMESPACE);
    if (comp->use == NULL)
	comp->has_use = 0;
    else
	comp->has_use = 1;
}