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
typedef  int /*<<< orphan*/  xmlXPathContextPtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  xmlXPathRegisterFunc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltCurrentFunction ; 
 int /*<<< orphan*/  xsltDocumentFunction ; 
 int /*<<< orphan*/  xsltElementAvailableFunction ; 
 int /*<<< orphan*/  xsltFormatNumberFunction ; 
 int /*<<< orphan*/  xsltFunctionAvailableFunction ; 
 int /*<<< orphan*/  xsltGenerateIdFunction ; 
 int /*<<< orphan*/  xsltKeyFunction ; 
 int /*<<< orphan*/  xsltSystemPropertyFunction ; 
 int /*<<< orphan*/  xsltUnparsedEntityURIFunction ; 

void
xsltRegisterAllFunctions(xmlXPathContextPtr ctxt)
{
    xmlXPathRegisterFunc(ctxt, (const xmlChar *) "current",
                         xsltCurrentFunction);
    xmlXPathRegisterFunc(ctxt, (const xmlChar *) "document",
                         xsltDocumentFunction);
    xmlXPathRegisterFunc(ctxt, (const xmlChar *) "key", xsltKeyFunction);
    xmlXPathRegisterFunc(ctxt, (const xmlChar *) "unparsed-entity-uri",
                         xsltUnparsedEntityURIFunction);
    xmlXPathRegisterFunc(ctxt, (const xmlChar *) "format-number",
                         xsltFormatNumberFunction);
    xmlXPathRegisterFunc(ctxt, (const xmlChar *) "generate-id",
                         xsltGenerateIdFunction);
    xmlXPathRegisterFunc(ctxt, (const xmlChar *) "system-property",
                         xsltSystemPropertyFunction);
    xmlXPathRegisterFunc(ctxt, (const xmlChar *) "element-available",
                         xsltElementAvailableFunction);
    xmlXPathRegisterFunc(ctxt, (const xmlChar *) "function-available",
                         xsltFunctionAvailableFunction);
}