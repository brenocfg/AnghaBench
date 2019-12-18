#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  acc; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int DISPATCH_JSCRIPT_CALLEREXECSSOURCE ; 
 int DISPATCH_METHOD ; 
 int /*<<< orphan*/  JS_E_INVALID_PROPERTY ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int const,int const) ; 
 int /*<<< orphan*/  clear_acc (TYPE_1__*) ; 
 int /*<<< orphan*/  disp_call_value (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int get_op_int (TYPE_1__*,int) ; 
 unsigned int get_op_uint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_args (TYPE_1__*,unsigned int const) ; 
 int /*<<< orphan*/  stack_topn (TYPE_1__*,unsigned int const) ; 
 int /*<<< orphan*/  throw_type_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_call(script_ctx_t *ctx)
{
    const unsigned argn = get_op_uint(ctx, 0);
    const int do_ret = get_op_int(ctx, 1);
    jsval_t obj;

    TRACE("%d %d\n", argn, do_ret);

    obj = stack_topn(ctx, argn);
    if(!is_object_instance(obj))
        return throw_type_error(ctx, JS_E_INVALID_PROPERTY, NULL);

    clear_acc(ctx);
    return disp_call_value(ctx, get_object(obj), NULL, DISPATCH_METHOD | DISPATCH_JSCRIPT_CALLEREXECSSOURCE,
                           argn, stack_args(ctx, argn), do_ret ? &ctx->acc : NULL);
}