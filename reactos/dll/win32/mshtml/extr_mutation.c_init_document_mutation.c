#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDocument ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_4__ {TYPE_2__ nsIDocumentObserver_iface; int /*<<< orphan*/  nsdoc; } ;
typedef  TYPE_1__ HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIDocument ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  content_utils ; 
 int /*<<< orphan*/  nsDocumentObserverVtbl ; 
 int /*<<< orphan*/  nsIContentUtils_AddDocumentObserver (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDocument_Release (int /*<<< orphan*/ *) ; 

void init_document_mutation(HTMLDocumentNode *doc)
{
    nsIDocument *nsdoc;
    nsresult nsres;

    doc->nsIDocumentObserver_iface.lpVtbl = &nsDocumentObserverVtbl;

    nsres = nsIDOMHTMLDocument_QueryInterface(doc->nsdoc, &IID_nsIDocument, (void**)&nsdoc);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDocument: %08x\n", nsres);
        return;
    }

    nsIContentUtils_AddDocumentObserver(content_utils, nsdoc, &doc->nsIDocumentObserver_iface);
    nsIDocument_Release(nsdoc);
}