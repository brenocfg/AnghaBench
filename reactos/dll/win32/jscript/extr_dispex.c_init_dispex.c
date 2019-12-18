#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int ref; int buf_size; int prop_cnt; int /*<<< orphan*/ * ctx; TYPE_10__* props; struct TYPE_17__* prototype; TYPE_5__ const* builtin_info; TYPE_1__ IDispatchEx_iface; } ;
typedef  TYPE_4__ jsdisp_t ;
typedef  int /*<<< orphan*/  dispex_prop_t ;
struct TYPE_16__ {scalar_t__ getter; scalar_t__ invoke; } ;
struct TYPE_18__ {TYPE_3__ value_prop; } ;
typedef  TYPE_5__ builtin_info_t ;
struct TYPE_15__ {TYPE_3__* p; } ;
struct TYPE_13__ {int /*<<< orphan*/  type; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchExVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  PROP_BUILTIN ; 
 int /*<<< orphan*/  PROP_DELETED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*,TYPE_4__*) ; 
 TYPE_10__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  jsdisp_addref (TYPE_4__*) ; 
 int /*<<< orphan*/  script_addref (int /*<<< orphan*/ *) ; 

HRESULT init_dispex(jsdisp_t *dispex, script_ctx_t *ctx, const builtin_info_t *builtin_info, jsdisp_t *prototype)
{
    TRACE("%p (%p)\n", dispex, prototype);

    dispex->IDispatchEx_iface.lpVtbl = &DispatchExVtbl;
    dispex->ref = 1;
    dispex->builtin_info = builtin_info;

    dispex->props = heap_alloc_zero(sizeof(dispex_prop_t)*(dispex->buf_size=4));
    if(!dispex->props)
        return E_OUTOFMEMORY;

    dispex->prototype = prototype;
    if(prototype)
        jsdisp_addref(prototype);

    dispex->prop_cnt = 1;
    if(builtin_info->value_prop.invoke || builtin_info->value_prop.getter) {
        dispex->props[0].type = PROP_BUILTIN;
        dispex->props[0].u.p = &builtin_info->value_prop;
    }else {
        dispex->props[0].type = PROP_DELETED;
    }

    script_addref(ctx);
    dispex->ctx = ctx;

    return S_OK;
}