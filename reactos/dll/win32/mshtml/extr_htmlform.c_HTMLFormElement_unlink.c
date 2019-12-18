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
typedef  int /*<<< orphan*/  nsIDOMHTMLFormElement ;
struct TYPE_3__ {int /*<<< orphan*/ * nsform; } ;
typedef  TYPE_1__ HTMLFormElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLFormElement_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLFormElement_unlink(HTMLDOMNode *iface)
{
    HTMLFormElement *This = impl_from_HTMLDOMNode(iface);

    if(This->nsform) {
        nsIDOMHTMLFormElement *nsform = This->nsform;

        This->nsform = NULL;
        nsIDOMHTMLFormElement_Release(nsform);
    }
}