#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  acc; } ;
typedef  TYPE_2__ script_ctx_t ;
struct TYPE_14__ {int /*<<< orphan*/  hres; } ;
struct TYPE_16__ {TYPE_1__ u; } ;
typedef  TYPE_3__ exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int DISPATCH_JSCRIPT_CALLEREXECSSOURCE ; 
 int DISPATCH_METHOD ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int const,int const) ; 
 int /*<<< orphan*/  clear_acc (TYPE_2__*) ; 
 int /*<<< orphan*/  exprval_call (TYPE_2__*,TYPE_3__*,int,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_op_int (TYPE_2__*,int) ; 
 unsigned int get_op_uint (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_args (TYPE_2__*,unsigned int const) ; 
 int /*<<< orphan*/  stack_topn_exprval (TYPE_2__*,unsigned int const,TYPE_3__*) ; 
 int /*<<< orphan*/  throw_type_error (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_call_member(script_ctx_t *ctx)
{
    const unsigned argn = get_op_uint(ctx, 0);
    const int do_ret = get_op_int(ctx, 1);
    exprval_t ref;

    TRACE("%d %d\n", argn, do_ret);

    if(!stack_topn_exprval(ctx, argn, &ref))
        return throw_type_error(ctx, ref.u.hres, NULL);

    clear_acc(ctx);
    return exprval_call(ctx, &ref, DISPATCH_METHOD | DISPATCH_JSCRIPT_CALLEREXECSSOURCE,
            argn, stack_args(ctx, argn), do_ret ? &ctx->acc : NULL);
}