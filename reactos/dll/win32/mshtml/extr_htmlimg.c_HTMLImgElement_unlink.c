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
typedef  int /*<<< orphan*/  nsIDOMHTMLImageElement ;
struct TYPE_3__ {int /*<<< orphan*/ * nsimg; } ;
typedef  TYPE_1__ HTMLImgElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLImageElement_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLImgElement_unlink(HTMLDOMNode *iface)
{
    HTMLImgElement *This = impl_from_HTMLDOMNode(iface);

    if(This->nsimg) {
        nsIDOMHTMLImageElement *nsimg = This->nsimg;

        This->nsimg = NULL;
        nsIDOMHTMLImageElement_Release(nsimg);
    }
}