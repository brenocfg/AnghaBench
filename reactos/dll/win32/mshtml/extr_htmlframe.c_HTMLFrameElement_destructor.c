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
struct TYPE_3__ {int /*<<< orphan*/  framebase; } ;
typedef  TYPE_1__ HTMLFrameElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLFrameBase_destructor (int /*<<< orphan*/ *) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLFrameElement_destructor(HTMLDOMNode *iface)
{
    HTMLFrameElement *This = impl_from_HTMLDOMNode(iface);

    HTMLFrameBase_destructor(&This->framebase);
}