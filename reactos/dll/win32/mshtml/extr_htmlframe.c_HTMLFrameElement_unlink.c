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
typedef  int /*<<< orphan*/  nsIDOMHTMLFrameElement ;
struct TYPE_4__ {int /*<<< orphan*/ * nsframe; } ;
struct TYPE_5__ {TYPE_1__ framebase; } ;
typedef  TYPE_2__ HTMLFrameElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 TYPE_2__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLFrameElement_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLFrameElement_unlink(HTMLDOMNode *iface)
{
    HTMLFrameElement *This = impl_from_HTMLDOMNode(iface);

    if(This->framebase.nsframe) {
        nsIDOMHTMLFrameElement *nsframe = This->framebase.nsframe;

        This->framebase.nsframe = NULL;
        nsIDOMHTMLFrameElement_Release(nsframe);
    }
}