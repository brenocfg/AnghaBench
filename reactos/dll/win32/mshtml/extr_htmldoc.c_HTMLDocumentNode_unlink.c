#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMHTMLDocument ;
struct TYPE_4__ {int /*<<< orphan*/ * window; int /*<<< orphan*/ * nsdoc; } ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_document_mutation (TYPE_1__*) ; 

__attribute__((used)) static void HTMLDocumentNode_unlink(HTMLDOMNode *iface)
{
    HTMLDocumentNode *This = impl_from_HTMLDOMNode(iface);

    if(This->nsdoc) {
        nsIDOMHTMLDocument *nsdoc = This->nsdoc;

        release_document_mutation(This);
        This->nsdoc = NULL;
        nsIDOMHTMLDocument_Release(nsdoc);
        This->window = NULL;
    }
}