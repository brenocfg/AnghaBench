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
typedef  TYPE_2__* xsltStyleItemValueOfPtr ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_16__ {scalar_t__ type; TYPE_2__* psvi; } ;
struct TYPE_15__ {int noescape; int /*<<< orphan*/ * select; int /*<<< orphan*/ * comp; TYPE_4__* inst; } ;
struct TYPE_14__ {int /*<<< orphan*/  errors; int /*<<< orphan*/  warnings; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  XSLT_FUNC_VALUEOF ; 
 int /*<<< orphan*/  XSLT_NAMESPACE ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 void* xsltGetCNsProp (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* xsltNewStylePreComp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/ * xsltXPathCompile (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xsltValueOfComp(xsltStylesheetPtr style, xmlNodePtr inst) {
#ifdef XSLT_REFACTORED
    xsltStyleItemValueOfPtr comp;
#else
    xsltStylePreCompPtr comp;
#endif
    const xmlChar *prop;

    if ((style == NULL) || (inst == NULL) || (inst->type != XML_ELEMENT_NODE))
	return;

#ifdef XSLT_REFACTORED
    comp = (xsltStyleItemValueOfPtr) xsltNewStylePreComp(style, XSLT_FUNC_VALUEOF);
#else
    comp = xsltNewStylePreComp(style, XSLT_FUNC_VALUEOF);
#endif

    if (comp == NULL)
	return;
    inst->psvi = comp;
    comp->inst = inst;

    prop = xsltGetCNsProp(style, inst,
	    (const xmlChar *)"disable-output-escaping",
			XSLT_NAMESPACE);
    if (prop != NULL) {
	if (xmlStrEqual(prop, (const xmlChar *)"yes")) {
	    comp->noescape = 1;
	} else if (!xmlStrEqual(prop,
				(const xmlChar *)"no")){
	    xsltTransformError(NULL, style, inst,
"xsl:value-of : disable-output-escaping allows only yes or no\n");
	    if (style != NULL) style->warnings++;
	}
    }
    comp->select = xsltGetCNsProp(style, inst, (const xmlChar *)"select",
	                        XSLT_NAMESPACE);
    if (comp->select == NULL) {
	xsltTransformError(NULL, style, inst,
	     "xsl:value-of : select is missing\n");
	if (style != NULL) style->errors++;
	return;
    }
    comp->comp = xsltXPathCompile(style, comp->select);
    if (comp->comp == NULL) {
	xsltTransformError(NULL, style, inst,
	     "xsl:value-of : could not compile select expression '%s'\n",
	                 comp->select);
	if (style != NULL) style->errors++;
    }
}