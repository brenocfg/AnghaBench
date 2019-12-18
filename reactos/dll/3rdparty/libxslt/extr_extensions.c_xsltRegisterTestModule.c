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
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 scalar_t__ XSLT_DEFAULT_URL ; 
 int /*<<< orphan*/  xsltExtElementPreCompTest ; 
 int /*<<< orphan*/  xsltExtElementTest ; 
 int /*<<< orphan*/  xsltExtFunctionTest ; 
 int /*<<< orphan*/  xsltExtInitTest ; 
 int /*<<< orphan*/  xsltExtShutdownTest ; 
 int /*<<< orphan*/  xsltExtStyleInitTest ; 
 int /*<<< orphan*/  xsltExtStyleShutdownTest ; 
 int /*<<< orphan*/  xsltInitGlobals () ; 
 int /*<<< orphan*/  xsltRegisterExtModuleElement (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltRegisterExtModuleFull (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltRegisterExtModuleFunction (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void
xsltRegisterTestModule(void)
{
    xsltInitGlobals();
    xsltRegisterExtModuleFull((const xmlChar *) XSLT_DEFAULT_URL,
                              xsltExtInitTest, xsltExtShutdownTest,
                              xsltExtStyleInitTest,
                              xsltExtStyleShutdownTest);
    xsltRegisterExtModuleFunction((const xmlChar *) "test",
                                  (const xmlChar *) XSLT_DEFAULT_URL,
                                  xsltExtFunctionTest);
    xsltRegisterExtModuleElement((const xmlChar *) "test",
                                 (const xmlChar *) XSLT_DEFAULT_URL,
                                 xsltExtElementPreCompTest,
                                 xsltExtElementTest);
}