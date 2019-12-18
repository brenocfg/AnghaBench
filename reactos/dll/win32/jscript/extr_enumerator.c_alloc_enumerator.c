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
struct TYPE_9__ {int /*<<< orphan*/  enumerator_constr; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_10__ {int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ EnumeratorInstance ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnumeratorInst_info ; 
 int /*<<< orphan*/  Enumerator_info ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dispex_from_constr (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT alloc_enumerator(script_ctx_t *ctx, jsdisp_t *object_prototype, EnumeratorInstance **ret)
{
    EnumeratorInstance *enumerator;
    HRESULT hres;

    enumerator = heap_alloc_zero(sizeof(EnumeratorInstance));
    if(!enumerator)
        return E_OUTOFMEMORY;

    if(object_prototype)
        hres = init_dispex(&enumerator->dispex, ctx, &Enumerator_info, object_prototype);
    else
        hres = init_dispex_from_constr(&enumerator->dispex, ctx, &EnumeratorInst_info,
                                       ctx->enumerator_constr);

    if(FAILED(hres))
    {
        heap_free(enumerator);
        return hres;
    }

    *ret = enumerator;
    return S_OK;
}