#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ret; TYPE_8__* ctxt; } ;
typedef  TYPE_1__ xsltInitExtCtxt ;
typedef  TYPE_2__* xsltExtModulePtr ;
typedef  TYPE_3__* xsltExtDataPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_13__ {int /*<<< orphan*/ * extInfos; } ;
struct TYPE_12__ {TYPE_2__* extModule; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* shutdownFunc ) (TYPE_8__*,int /*<<< orphan*/  const*,void*) ;void* (* initFunc ) (TYPE_8__*,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 void* stub1 (TYPE_8__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*,int /*<<< orphan*/  const*,void*) ; 
 scalar_t__ xmlHashAddEntry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*) ; 
 int /*<<< orphan*/ * xmlHashCreate (int) ; 
 scalar_t__ xmlHashLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltFreeExtData (TYPE_3__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltGenericError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericErrorContext ; 
 TYPE_3__* xsltNewExtData (TYPE_2__*,void*) ; 

__attribute__((used)) static void
xsltInitCtxtExt(void *payload, void *data, const xmlChar * URI)
{
    xsltExtDataPtr styleData = (xsltExtDataPtr) payload;
    xsltInitExtCtxt *ctxt = (xsltInitExtCtxt *) data;
    xsltExtModulePtr module;
    xsltExtDataPtr ctxtData;
    void *extData;

    if ((styleData == NULL) || (ctxt == NULL) || (URI == NULL) ||
        (ctxt->ret == -1)) {
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
        xsltGenericDebug(xsltGenericDebugContext,
                         "xsltInitCtxtExt: NULL param or error\n");
#endif
        return;
    }
    module = styleData->extModule;
    if ((module == NULL) || (module->initFunc == NULL)) {
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
        xsltGenericDebug(xsltGenericDebugContext,
                         "xsltInitCtxtExt: no module or no initFunc\n");
#endif
        return;
    }

    ctxtData = (xsltExtDataPtr) xmlHashLookup(ctxt->ctxt->extInfos, URI);
    if (ctxtData != NULL) {
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
        xsltGenericDebug(xsltGenericDebugContext,
                         "xsltInitCtxtExt: already initialized\n");
#endif
        return;
    }

    extData = module->initFunc(ctxt->ctxt, URI);
    if (extData == NULL) {
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
        xsltGenericDebug(xsltGenericDebugContext,
                         "xsltInitCtxtExt: no extData\n");
#endif
    }
    ctxtData = xsltNewExtData(module, extData);
    if (ctxtData == NULL) {
        ctxt->ret = -1;
        return;
    }

    if (ctxt->ctxt->extInfos == NULL)
        ctxt->ctxt->extInfos = xmlHashCreate(10);
    if (ctxt->ctxt->extInfos == NULL) {
        ctxt->ret = -1;
        return;
    }

    if (xmlHashAddEntry(ctxt->ctxt->extInfos, URI, ctxtData) < 0) {
        xsltGenericError(xsltGenericErrorContext,
                         "Failed to register module data: %s\n", URI);
        if (module->shutdownFunc)
            module->shutdownFunc(ctxt->ctxt, URI, extData);
        xsltFreeExtData(ctxtData);
        ctxt->ret = -1;
        return;
    }
#ifdef WITH_XSLT_DEBUG_EXTENSIONS
    xsltGenericDebug(xsltGenericDebugContext, "Registered module %s\n",
                     URI);
#endif
    ctxt->ret++;
}