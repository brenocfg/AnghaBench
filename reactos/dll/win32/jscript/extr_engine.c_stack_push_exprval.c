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
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  disp; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  hres; int /*<<< orphan*/  off; TYPE_1__ idref; } ;
struct TYPE_7__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
#define  EXPRVAL_IDREF 131 
#define  EXPRVAL_INVALID 130 
#define  EXPRVAL_JSVAL 129 
#define  EXPRVAL_STACK_REF 128 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT stack_push_exprval(script_ctx_t *ctx, exprval_t *val)
{
    HRESULT hres;

    switch(val->type) {
    case EXPRVAL_JSVAL:
        assert(0);
    case EXPRVAL_IDREF:
        hres = stack_push(ctx, jsval_disp(val->u.idref.disp));
        if(SUCCEEDED(hres))
            hres = stack_push(ctx, jsval_number(val->u.idref.id));
        else
            IDispatch_Release(val->u.idref.disp);
        return hres;
    case EXPRVAL_STACK_REF:
        hres = stack_push(ctx, jsval_number(val->u.off));
        if(SUCCEEDED(hres))
            hres = stack_push(ctx, jsval_undefined());
        return hres;
    case EXPRVAL_INVALID:
        hres = stack_push(ctx, jsval_undefined());
        if(SUCCEEDED(hres))
            hres = stack_push(ctx, jsval_number(val->u.hres));
        return hres;
    }

    assert(0);
    return E_FAIL;
}