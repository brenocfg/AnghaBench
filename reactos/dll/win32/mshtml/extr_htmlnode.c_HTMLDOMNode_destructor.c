#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ptr; } ;
struct TYPE_7__ {TYPE_2__ event_target; TYPE_1__* doc; scalar_t__ nsnode; } ;
struct TYPE_5__ {int /*<<< orphan*/  basedoc; TYPE_3__ node; } ;
typedef  TYPE_3__ HTMLDOMNode ;

/* Variables and functions */
 int /*<<< orphan*/  htmldoc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (scalar_t__) ; 
 int /*<<< orphan*/  release_event_target (scalar_t__) ; 

void HTMLDOMNode_destructor(HTMLDOMNode *This)
{
    if(This->nsnode)
        nsIDOMNode_Release(This->nsnode);
    if(This->doc && &This->doc->node != This)
        htmldoc_release(&This->doc->basedoc);
    if(This->event_target.ptr)
        release_event_target(This->event_target.ptr);
}