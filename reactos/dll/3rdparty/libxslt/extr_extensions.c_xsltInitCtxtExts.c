#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylesheetPtr ;
struct TYPE_10__ {int ret; TYPE_1__* ctxt; } ;
typedef  TYPE_3__ xsltInitExtCtxt ;
struct TYPE_9__ {int /*<<< orphan*/ * extInfos; } ;
struct TYPE_8__ {TYPE_2__* style; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlHashScan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltInitCtxtExt ; 
 TYPE_2__* xsltNextImport (TYPE_2__*) ; 

int
xsltInitCtxtExts(xsltTransformContextPtr ctxt)
{
    xsltStylesheetPtr style;
    xsltInitExtCtxt ctx;

    if (ctxt == NULL)
        return (-1);

    style = ctxt->style;
    if (style == NULL)
        return (-1);

    ctx.ctxt = ctxt;
    ctx.ret = 0;

    while (style != NULL) {
        if (style->extInfos != NULL) {
            xmlHashScan(style->extInfos, xsltInitCtxtExt, &ctx);
            if (ctx.ret == -1)
                return (-1);
        }
        style = xsltNextImport(style);
    }
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
    xsltGenericDebug(xsltGenericDebugContext, "Registered %d modules\n",
                     ctx.ret);
#endif
    return (ctx.ret);
}