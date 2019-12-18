#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYPUT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_ILLEGAL_ASSIGN ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int const) ; 
 int /*<<< orphan*/  exprval_call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int get_op_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_args (int /*<<< orphan*/ *,unsigned int const) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_popn (int /*<<< orphan*/ *,unsigned int const) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_topn_exprval (int /*<<< orphan*/ *,unsigned int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_reference_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_assign_call(script_ctx_t *ctx)
{
    const unsigned argc = get_op_uint(ctx, 0);
    exprval_t ref;
    jsval_t v;
    HRESULT hres;

    TRACE("%u\n", argc);

    if(!stack_topn_exprval(ctx, argc+1, &ref))
        return throw_reference_error(ctx, JS_E_ILLEGAL_ASSIGN, NULL);

    hres = exprval_call(ctx, &ref, DISPATCH_PROPERTYPUT, argc+1, stack_args(ctx, argc+1), NULL);
    if(FAILED(hres))
        return hres;

    v = stack_pop(ctx);
    stack_popn(ctx, argc+2);
    return stack_push(ctx, v);
}