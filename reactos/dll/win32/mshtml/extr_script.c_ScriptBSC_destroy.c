#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* buf; TYPE_1__* script_elem; } ;
struct TYPE_5__ {int /*<<< orphan*/  IHTMLScriptElement_iface; } ;
typedef  TYPE_2__ ScriptBSC ;
typedef  int /*<<< orphan*/  BSCallback ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLScriptElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 TYPE_2__* impl_from_BSCallback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ScriptBSC_destroy(BSCallback *bsc)
{
    ScriptBSC *This = impl_from_BSCallback(bsc);

    if(This->script_elem) {
        IHTMLScriptElement_Release(&This->script_elem->IHTMLScriptElement_iface);
        This->script_elem = NULL;
    }

    heap_free(This->buf);
    heap_free(This);
}