#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  disp; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ idref; } ;
struct TYPE_8__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  EXPRVAL_IDREF 130 
#define  EXPRVAL_INVALID 129 
#define  EXPRVAL_STACK_REF 128 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  disp_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprval_release (TYPE_3__*) ; 
 int /*<<< orphan*/  get_op_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identifier_eval (int /*<<< orphan*/ *,int /*<<< orphan*/  const,TYPE_3__*) ; 
 int /*<<< orphan*/  jsval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT interp_delete_ident(script_ctx_t *ctx)
{
    const BSTR arg = get_op_bstr(ctx, 0);
    exprval_t exprval;
    BOOL ret;
    HRESULT hres;

    TRACE("%s\n", debugstr_w(arg));

    hres = identifier_eval(ctx, arg, &exprval);
    if(FAILED(hres))
        return hres;

    switch(exprval.type) {
    case EXPRVAL_STACK_REF:
        ret = FALSE;
        break;
    case EXPRVAL_IDREF:
        hres = disp_delete(exprval.u.idref.disp, exprval.u.idref.id, &ret);
        IDispatch_Release(exprval.u.idref.disp);
        if(FAILED(hres))
            return hres;
        break;
    case EXPRVAL_INVALID:
        ret = TRUE;
        break;
    default:
        FIXME("Unsupported exprval\n");
        exprval_release(&exprval);
        return E_NOTIMPL;
    }


    return stack_push(ctx, jsval_bool(ret));
}