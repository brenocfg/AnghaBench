#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltTransformContextPtr ;
typedef  TYPE_1__* xsltExtModulePtr ;
typedef  TYPE_2__* xsltExtDataPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {int /*<<< orphan*/  extData; TYPE_1__* extModule; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* shutdownFunc ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 

__attribute__((used)) static void
xsltShutdownCtxtExt(void *payload, void *vctxt, const xmlChar * URI)
{
    xsltExtDataPtr data = (xsltExtDataPtr) payload;
    xsltTransformContextPtr ctxt = (xsltTransformContextPtr) vctxt;
    xsltExtModulePtr module;

    if ((data == NULL) || (ctxt == NULL) || (URI == NULL))
        return;
    module = data->extModule;
    if ((module == NULL) || (module->shutdownFunc == NULL))
        return;

#ifdef WITH_XSLT_DEBUG_EXTENSIONS
    xsltGenericDebug(xsltGenericDebugContext,
                     "Shutting down module : %s\n", URI);
#endif
    module->shutdownFunc(ctxt, URI, data->extData);
}