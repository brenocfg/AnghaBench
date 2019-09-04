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
 void* testData ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
xsltExtShutdownTest(xsltTransformContextPtr ctxt,
                    const xmlChar * URI, void *data)
{
    if (testData == NULL) {
        xsltTransformError(ctxt, NULL, NULL,
                           "xsltExtShutdownTest: not initialized\n");
        return;
    }
    if (data != testData) {
        xsltTransformError(ctxt, NULL, NULL,
                           "xsltExtShutdownTest: wrong data\n");
    }
    testData = NULL;
    xsltGenericDebug(xsltGenericDebugContext,
                     "Unregistered test module : %s\n", URI);
}