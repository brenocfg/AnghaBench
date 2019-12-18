#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  number_constr; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_10__ {int /*<<< orphan*/  dispex; } ;
typedef  TYPE_2__ NumberInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NumberInst_info ; 
 int /*<<< orphan*/  Number_info ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dispex_from_constr (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT alloc_number(script_ctx_t *ctx, jsdisp_t *object_prototype, NumberInstance **ret)
{
    NumberInstance *number;
    HRESULT hres;

    number = heap_alloc_zero(sizeof(NumberInstance));
    if(!number)
        return E_OUTOFMEMORY;

    if(object_prototype)
        hres = init_dispex(&number->dispex, ctx, &Number_info, object_prototype);
    else
        hres = init_dispex_from_constr(&number->dispex, ctx, &NumberInst_info, ctx->number_constr);
    if(FAILED(hres)) {
        heap_free(number);
        return hres;
    }

    *ret = number;
    return S_OK;
}