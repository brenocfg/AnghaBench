#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ref; int /*<<< orphan*/ * next; int /*<<< orphan*/ * frame; int /*<<< orphan*/ * obj; int /*<<< orphan*/ * jsobj; } ;
typedef  TYPE_1__ scope_chain_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/ * scope_addref (TYPE_1__*) ; 

__attribute__((used)) static HRESULT scope_push(scope_chain_t *scope, jsdisp_t *jsobj, IDispatch *obj, scope_chain_t **ret)
{
    scope_chain_t *new_scope;

    new_scope = heap_alloc(sizeof(scope_chain_t));
    if(!new_scope)
        return E_OUTOFMEMORY;

    new_scope->ref = 1;

    IDispatch_AddRef(obj);
    new_scope->jsobj = jsobj;
    new_scope->obj = obj;
    new_scope->frame = NULL;
    new_scope->next = scope ? scope_addref(scope) : NULL;

    *ret = new_scope;
    return S_OK;
}