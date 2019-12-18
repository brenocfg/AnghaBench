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
typedef  int /*<<< orphan*/  nsIDOMHTMLIFrameElement ;
struct TYPE_4__ {int /*<<< orphan*/ * nsiframe; } ;
struct TYPE_5__ {TYPE_1__ framebase; } ;
typedef  TYPE_2__ HTMLIFrame ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 TYPE_2__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLIFrameElement_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLIFrame_unlink(HTMLDOMNode *iface)
{
    HTMLIFrame *This = impl_from_HTMLDOMNode(iface);

    if(This->framebase.nsiframe) {
        nsIDOMHTMLIFrameElement *nsiframe = This->framebase.nsiframe;

        This->framebase.nsiframe = NULL;
        nsIDOMHTMLIFrameElement_Release(nsiframe);
    }
}