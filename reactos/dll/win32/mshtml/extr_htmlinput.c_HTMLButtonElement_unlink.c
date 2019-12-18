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
typedef  int /*<<< orphan*/  nsIDOMHTMLButtonElement ;
struct TYPE_3__ {int /*<<< orphan*/ * nsbutton; } ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  TYPE_1__ HTMLButtonElement ;

/* Variables and functions */
 TYPE_1__* button_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLButtonElement_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLButtonElement_unlink(HTMLDOMNode *iface)
{
    HTMLButtonElement *This = button_from_HTMLDOMNode(iface);

    if(This->nsbutton) {
        nsIDOMHTMLButtonElement *nsbutton = This->nsbutton;

        This->nsbutton = NULL;
        nsIDOMHTMLButtonElement_Release(nsbutton);
    }
}