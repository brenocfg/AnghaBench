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
struct TYPE_4__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ variant_val_t ;
typedef  int /*<<< orphan*/  exec_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_val (TYPE_1__*) ; 
 int /*<<< orphan*/  stack_pop_val (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  var_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT cmp_oper(exec_ctx_t *ctx)
{
    variant_val_t l, r;
    HRESULT hres;

    hres = stack_pop_val(ctx, &r);
    if(FAILED(hres))
        return hres;

    hres = stack_pop_val(ctx, &l);
    if(SUCCEEDED(hres)) {
        hres = var_cmp(ctx, l.v, r.v);
        release_val(&l);
    }

    release_val(&r);
    return hres;
}