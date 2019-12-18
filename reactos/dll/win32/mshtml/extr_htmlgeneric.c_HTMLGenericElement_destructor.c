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
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct TYPE_5__ {TYPE_1__ element; } ;
typedef  TYPE_2__ HTMLGenericElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLElement_destructor (int /*<<< orphan*/ *) ; 
 TYPE_2__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLGenericElement_destructor(HTMLDOMNode *iface)
{
    HTMLGenericElement *This = impl_from_HTMLDOMNode(iface);

    HTMLElement_destructor(&This->element.node);
}