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
typedef  int /*<<< orphan*/  nsIDOMHTMLAnchorElement ;
struct TYPE_3__ {int /*<<< orphan*/ * nsanchor; } ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  TYPE_1__ HTMLAnchorElement ;

/* Variables and functions */
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLAnchorElement_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLAnchorElement_unlink(HTMLDOMNode *iface)
{
    HTMLAnchorElement *This = impl_from_HTMLDOMNode(iface);

    if(This->nsanchor) {
        nsIDOMHTMLAnchorElement *nsanchor = This->nsanchor;

        This->nsanchor = NULL;
        nsIDOMHTMLAnchorElement_Release(nsanchor);
    }
}