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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * disp; } ;
struct TYPE_7__ {TYPE_1__ idref; } ;
struct TYPE_8__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ exprval_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  EXPRVAL_IDREF ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JS_E_INVALID_PROPERTY ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int const) ; 
 scalar_t__ disp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprval_set_exception (TYPE_3__*,int /*<<< orphan*/ ) ; 
 unsigned int const fdexNameEnsure ; 
 unsigned int get_op_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 scalar_t__ stack_push_exprval (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 
 scalar_t__ to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT interp_memberid(script_ctx_t *ctx)
{
    const unsigned arg = get_op_uint(ctx, 0);
    jsval_t objv, namev;
    const WCHAR *name;
    jsstr_t *name_str;
    IDispatch *obj;
    exprval_t ref;
    DISPID id;
    HRESULT hres;

    TRACE("%x\n", arg);

    namev = stack_pop(ctx);
    objv = stack_pop(ctx);

    hres = to_object(ctx, objv, &obj);
    jsval_release(objv);
    if(SUCCEEDED(hres)) {
        hres = to_flat_string(ctx, namev, &name_str, &name);
        if(FAILED(hres))
            IDispatch_Release(obj);
    }
    jsval_release(namev);
    if(FAILED(hres))
        return hres;

    hres = disp_get_id(ctx, obj, name, NULL, arg, &id);
    jsstr_release(name_str);
    if(SUCCEEDED(hres)) {
        ref.type = EXPRVAL_IDREF;
        ref.u.idref.disp = obj;
        ref.u.idref.id = id;
    }else {
        IDispatch_Release(obj);
        if(hres == DISP_E_UNKNOWNNAME && !(arg & fdexNameEnsure)) {
            exprval_set_exception(&ref, JS_E_INVALID_PROPERTY);
            hres = S_OK;
        }else {
            ERR("failed %08x\n", hres);
            return hres;
        }
    }

    return stack_push_exprval(ctx, &ref);
}