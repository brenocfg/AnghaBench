#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int bstr_cnt; struct TYPE_5__* instrs; struct TYPE_5__* source; struct TYPE_5__* bstr_pool; int /*<<< orphan*/  heap; scalar_t__ context; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ vbscode_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_Release (scalar_t__) ; 
 int /*<<< orphan*/  SysFreeString (TYPE_1__) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

void release_vbscode(vbscode_t *code)
{
    unsigned i;

    list_remove(&code->entry);

    for(i=0; i < code->bstr_cnt; i++)
        SysFreeString(code->bstr_pool[i]);

    if(code->context)
        IDispatch_Release(code->context);
    heap_pool_free(&code->heap);

    heap_free(code->bstr_pool);
    heap_free(code->source);
    heap_free(code->instrs);
    heap_free(code);
}