#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltTransformContextPtr ;
typedef  TYPE_1__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  XSLT_TRACE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_TEMPLATES ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xsltAttrTemplateValueProcessNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/ * xsltGetNsProp (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

xmlChar *
xsltEvalAttrValueTemplate(xsltTransformContextPtr ctxt, xmlNodePtr inst,
	                  const xmlChar *name, const xmlChar *ns)
{
    xmlChar *ret;
    xmlChar *expr;

    if ((ctxt == NULL) || (inst == NULL) || (name == NULL) ||
        (inst->type != XML_ELEMENT_NODE))
	return(NULL);

    expr = xsltGetNsProp(inst, name, ns);
    if (expr == NULL)
	return(NULL);

    /*
     * TODO: though now {} is detected ahead, it would still be good to
     *       optimize both functions to keep the splitted value if the
     *       attribute content and the XPath precompiled expressions around
     */

    ret = xsltAttrTemplateValueProcessNode(ctxt, expr, inst);
#ifdef WITH_XSLT_DEBUG_TEMPLATES
    XSLT_TRACE(ctxt,XSLT_TRACE_TEMPLATES,xsltGenericDebug(xsltGenericDebugContext,
	 "xsltEvalAttrValueTemplate: %s returns %s\n", expr, ret));
#endif
    if (expr != NULL)
	xmlFree(expr);
    return(ret);
}