#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xmlDocPtr ;
struct TYPE_13__ {scalar_t__ psvi; scalar_t__ next; int /*<<< orphan*/ * prev; } ;
struct TYPE_12__ {TYPE_2__* localRVT; } ;

/* Variables and functions */
 scalar_t__ XSLT_RVT_FUNC_RESULT ; 
 scalar_t__ XSLT_RVT_GLOBAL ; 
 scalar_t__ XSLT_RVT_LOCAL ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xsltRegisterLocalRVT (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltRegisterPersistRVT (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltReleaseRVT (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
xsltReleaseLocalRVTs(xsltTransformContextPtr ctxt, xmlDocPtr base)
{
    xmlDocPtr cur = ctxt->localRVT, tmp;

    if (cur == base)
        return;
    if (cur->prev != NULL)
        xsltTransformError(ctxt, NULL, NULL, "localRVT not head of list\n");

    /* Reset localRVT early because some RVTs might be registered again. */
    ctxt->localRVT = base;
    if (base != NULL)
        base->prev = NULL;

    do {
        tmp = cur;
        cur = (xmlDocPtr) cur->next;
        if (tmp->psvi == XSLT_RVT_LOCAL) {
            xsltReleaseRVT(ctxt, tmp);
        } else if (tmp->psvi == XSLT_RVT_GLOBAL) {
            xsltRegisterPersistRVT(ctxt, tmp);
        } else if (tmp->psvi == XSLT_RVT_FUNC_RESULT) {
            /*
             * This will either register the RVT again or move it to the
             * context variable.
             */
            xsltRegisterLocalRVT(ctxt, tmp);
            tmp->psvi = XSLT_RVT_FUNC_RESULT;
        } else {
            xmlGenericError(xmlGenericErrorContext,
                    "xsltReleaseLocalRVTs: Unexpected RVT flag %p\n",
                    tmp->psvi);
        }
    } while (cur != base);
}