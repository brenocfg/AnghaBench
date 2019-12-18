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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ exprval_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ EXPRVAL_INVALID ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  exprval_to_value (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_op_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identifier_eval (int /*<<< orphan*/ *,int /*<<< orphan*/  const,TYPE_1__*) ; 
 int /*<<< orphan*/  jsstr_undefined () ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_push_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  typeof_string (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT interp_typeofident(script_ctx_t *ctx)
{
    const BSTR arg = get_op_bstr(ctx, 0);
    exprval_t exprval;
    const WCHAR *ret;
    jsval_t v;
    HRESULT hres;

    TRACE("%s\n", debugstr_w(arg));

    hres = identifier_eval(ctx, arg, &exprval);
    if(FAILED(hres))
        return hres;

    if(exprval.type == EXPRVAL_INVALID)
        return stack_push(ctx, jsval_string(jsstr_undefined()));

    hres = exprval_to_value(ctx, &exprval, &v);
    if(FAILED(hres))
        return hres;

    hres = typeof_string(v, &ret);
    jsval_release(v);
    if(FAILED(hres))
        return hres;

    return stack_push_string(ctx, ret);
}