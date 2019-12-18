#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  int /*<<< orphan*/  xsltTransformContext ;
struct TYPE_12__ {int /*<<< orphan*/ * nsHash; } ;
struct TYPE_11__ {scalar_t__ extrasNr; int /*<<< orphan*/  dict; int /*<<< orphan*/  cache; struct TYPE_11__* extras; int /*<<< orphan*/ * info; int /*<<< orphan*/  (* deallocate ) (int /*<<< orphan*/ *) ;struct TYPE_11__* profTab; struct TYPE_11__* varsTab; struct TYPE_11__* templTab; TYPE_8__* xpathCtxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlDictFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlXPathFreeContext (TYPE_8__*) ; 
 int /*<<< orphan*/  xsltFreeCtxtExts (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeDocuments (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeGlobalVariables (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeRVTs (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltShutdownCtxtExts (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltTransformCacheFree (int /*<<< orphan*/ ) ; 

void
xsltFreeTransformContext(xsltTransformContextPtr ctxt) {
    if (ctxt == NULL)
	return;

    /*
     * Shutdown the extension modules associated to the stylesheet
     * used if needed.
     */
    xsltShutdownCtxtExts(ctxt);

    if (ctxt->xpathCtxt != NULL) {
	ctxt->xpathCtxt->nsHash = NULL;
	xmlXPathFreeContext(ctxt->xpathCtxt);
    }
    if (ctxt->templTab != NULL)
	xmlFree(ctxt->templTab);
    if (ctxt->varsTab != NULL)
	xmlFree(ctxt->varsTab);
    if (ctxt->profTab != NULL)
	xmlFree(ctxt->profTab);
    if ((ctxt->extrasNr > 0) && (ctxt->extras != NULL)) {
	int i;

	for (i = 0;i < ctxt->extrasNr;i++) {
	    if ((ctxt->extras[i].deallocate != NULL) &&
		(ctxt->extras[i].info != NULL))
		ctxt->extras[i].deallocate(ctxt->extras[i].info);
	}
	xmlFree(ctxt->extras);
    }
    xsltFreeGlobalVariables(ctxt);
    xsltFreeDocuments(ctxt);
    xsltFreeCtxtExts(ctxt);
    xsltFreeRVTs(ctxt);
    xsltTransformCacheFree(ctxt->cache);
    xmlDictFree(ctxt->dict);
#ifdef WITH_XSLT_DEBUG
    xsltGenericDebug(xsltGenericDebugContext,
                     "freeing transformation dictionary\n");
#endif
    memset(ctxt, -1, sizeof(xsltTransformContext));
    xmlFree(ctxt);
}