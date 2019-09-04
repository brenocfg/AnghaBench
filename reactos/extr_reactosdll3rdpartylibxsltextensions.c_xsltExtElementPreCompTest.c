#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformFunction ;
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/ * xsltElemPreCompPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_6__ {int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 scalar_t__ XSLT_DEFAULT_URL ; 
 int /*<<< orphan*/ * testStyleData ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/ * xsltNewElemPreComp (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltStyleGetExtData (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static xsltElemPreCompPtr
xsltExtElementPreCompTest(xsltStylesheetPtr style, xmlNodePtr inst,
                          xsltTransformFunction function)
{
    xsltElemPreCompPtr ret;

    if (style == NULL) {
        xsltTransformError(NULL, NULL, inst,
                           "xsltExtElementTest: no transformation context\n");
        return (NULL);
    }
    if (testStyleData == NULL) {
        xsltGenericDebug(xsltGenericDebugContext,
                         "xsltExtElementPreCompTest: not initialized,"
                         " calling xsltStyleGetExtData\n");
        xsltStyleGetExtData(style, (const xmlChar *) XSLT_DEFAULT_URL);
        if (testStyleData == NULL) {
            xsltTransformError(NULL, style, inst,
                               "xsltExtElementPreCompTest: not initialized\n");
            if (style != NULL)
                style->errors++;
            return (NULL);
        }
    }
    if (inst == NULL) {
        xsltTransformError(NULL, style, inst,
                           "xsltExtElementPreCompTest: no instruction\n");
        if (style != NULL)
            style->errors++;
        return (NULL);
    }
    ret = xsltNewElemPreComp(style, inst, function);
    return (ret);
}