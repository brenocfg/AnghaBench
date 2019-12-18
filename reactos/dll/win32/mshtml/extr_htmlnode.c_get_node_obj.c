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
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  TYPE_1__ IHTMLDOMNode ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLDOMNodeVtbl ; 
 int /*<<< orphan*/ * impl_from_IHTMLDOMNode (TYPE_1__*) ; 
 int /*<<< orphan*/  node_addref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HTMLDOMNode *get_node_obj(IHTMLDOMNode *iface)
{
    HTMLDOMNode *ret;

    if(iface->lpVtbl != &HTMLDOMNodeVtbl)
        return NULL;

    ret = impl_from_IHTMLDOMNode(iface);
    node_addref(ret);
    return ret;
}