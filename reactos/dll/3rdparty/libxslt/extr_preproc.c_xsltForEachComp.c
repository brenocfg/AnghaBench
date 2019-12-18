#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  TYPE_2__* xsltStyleItemForEachPtr ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_16__ {scalar_t__ type; TYPE_2__* psvi; } ;
struct TYPE_15__ {int /*<<< orphan*/ * select; int /*<<< orphan*/ * comp; TYPE_4__* inst; } ;
struct TYPE_14__ {int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  XSLT_FUNC_FOREACH ; 
 int /*<<< orphan*/  XSLT_NAMESPACE ; 
 int /*<<< orphan*/ * xsltGetCNsProp (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* xsltNewStylePreComp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/ * xsltXPathCompile (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xsltForEachComp(xsltStylesheetPtr style, xmlNodePtr inst) {
#ifdef XSLT_REFACTORED
    xsltStyleItemForEachPtr comp;
#else
    xsltStylePreCompPtr comp;
#endif

    if ((style == NULL) || (inst == NULL) || (inst->type != XML_ELEMENT_NODE))
	return;

#ifdef XSLT_REFACTORED
    comp = (xsltStyleItemForEachPtr)
	xsltNewStylePreComp(style, XSLT_FUNC_FOREACH);
#else
    comp = xsltNewStylePreComp(style, XSLT_FUNC_FOREACH);
#endif

    if (comp == NULL)
	return;
    inst->psvi = comp;
    comp->inst = inst;

    comp->select = xsltGetCNsProp(style, inst, (const xmlChar *)"select",
	                        XSLT_NAMESPACE);
    if (comp->select == NULL) {
	xsltTransformError(NULL, style, inst,
		"xsl:for-each : select is missing\n");
	if (style != NULL) style->errors++;
    } else {
	comp->comp = xsltXPathCompile(style, comp->select);
	if (comp->comp == NULL) {
	    xsltTransformError(NULL, style, inst,
     "xsl:for-each : could not compile select expression '%s'\n",
			     comp->select);
	    if (style != NULL) style->errors++;
	}
    }
    /* TODO: handle and skip the xsl:sort */
}