#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_NAMESPACE ; 
 int /*<<< orphan*/  xsltApplyImports ; 
 int /*<<< orphan*/  xsltApplyTemplates ; 
 int /*<<< orphan*/  xsltAttribute ; 
 int /*<<< orphan*/  xsltCallTemplate ; 
 int /*<<< orphan*/  xsltChoose ; 
 int /*<<< orphan*/  xsltComment ; 
 int /*<<< orphan*/  xsltCopy ; 
 int /*<<< orphan*/  xsltCopyOf ; 
 int /*<<< orphan*/  xsltDebug ; 
 int /*<<< orphan*/  xsltElement ; 
 int /*<<< orphan*/  xsltForEach ; 
 int /*<<< orphan*/  xsltIf ; 
 int /*<<< orphan*/  xsltMessageWrapper ; 
 int /*<<< orphan*/  xsltNumber ; 
 int /*<<< orphan*/  xsltProcessingInstruction ; 
 int /*<<< orphan*/  xsltRegisterExtElement (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltSort ; 
 int /*<<< orphan*/  xsltText ; 
 int /*<<< orphan*/  xsltValueOf ; 

void
xsltRegisterAllElement(xsltTransformContextPtr ctxt)
{
    xsltRegisterExtElement(ctxt, (const xmlChar *) "apply-templates",
                           XSLT_NAMESPACE,
			   xsltApplyTemplates);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "apply-imports",
                           XSLT_NAMESPACE,
			   xsltApplyImports);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "call-template",
                           XSLT_NAMESPACE,
			   xsltCallTemplate);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "element",
                           XSLT_NAMESPACE,
			   xsltElement);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "attribute",
                           XSLT_NAMESPACE,
			   xsltAttribute);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "text",
                           XSLT_NAMESPACE,
			   xsltText);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "processing-instruction",
                           XSLT_NAMESPACE,
			   xsltProcessingInstruction);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "comment",
                           XSLT_NAMESPACE,
			   xsltComment);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "copy",
                           XSLT_NAMESPACE,
			   xsltCopy);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "value-of",
                           XSLT_NAMESPACE,
			   xsltValueOf);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "number",
                           XSLT_NAMESPACE,
			   xsltNumber);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "for-each",
                           XSLT_NAMESPACE,
			   xsltForEach);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "if",
                           XSLT_NAMESPACE,
			   xsltIf);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "choose",
                           XSLT_NAMESPACE,
			   xsltChoose);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "sort",
                           XSLT_NAMESPACE,
			   xsltSort);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "copy-of",
                           XSLT_NAMESPACE,
			   xsltCopyOf);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "message",
                           XSLT_NAMESPACE,
			   xsltMessageWrapper);

    /*
     * Those don't have callable entry points but are registered anyway
     */
    xsltRegisterExtElement(ctxt, (const xmlChar *) "variable",
                           XSLT_NAMESPACE,
			   xsltDebug);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "param",
                           XSLT_NAMESPACE,
			   xsltDebug);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "with-param",
                           XSLT_NAMESPACE,
			   xsltDebug);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "decimal-format",
                           XSLT_NAMESPACE,
			   xsltDebug);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "when",
                           XSLT_NAMESPACE,
			   xsltDebug);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "otherwise",
                           XSLT_NAMESPACE,
			   xsltDebug);
    xsltRegisterExtElement(ctxt, (const xmlChar *) "fallback",
                           XSLT_NAMESPACE,
			   xsltDebug);

}