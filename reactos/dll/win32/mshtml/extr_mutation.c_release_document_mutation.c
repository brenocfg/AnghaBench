#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDocument ;
struct TYPE_3__ {int /*<<< orphan*/  nsIDocumentObserver_iface; int /*<<< orphan*/  nsdoc; } ;
typedef  TYPE_1__ HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIDocument ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  content_utils ; 
 int /*<<< orphan*/  nsIContentUtils_RemoveDocumentObserver (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDocument_Release (int /*<<< orphan*/ *) ; 

void release_document_mutation(HTMLDocumentNode *doc)
{
    nsIDocument *nsdoc;
    nsresult nsres;

    nsres = nsIDOMHTMLDocument_QueryInterface(doc->nsdoc, &IID_nsIDocument, (void**)&nsdoc);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDocument: %08x\n", nsres);
        return;
    }

    nsIContentUtils_RemoveDocumentObserver(content_utils, nsdoc, &doc->nsIDocumentObserver_iface);
    nsIDocument_Release(nsdoc);
}