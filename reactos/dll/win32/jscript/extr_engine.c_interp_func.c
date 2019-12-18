#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* call_ctx; } ;
typedef  TYPE_2__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_10__ {int /*<<< orphan*/  scope; TYPE_1__* function; int /*<<< orphan*/  bytecode; } ;
typedef  TYPE_3__ call_frame_t ;
struct TYPE_8__ {scalar_t__ funcs; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int) ; 
 int /*<<< orphan*/  create_source_function (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 unsigned int get_op_uint (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT interp_func(script_ctx_t *ctx)
{
    unsigned func_idx = get_op_uint(ctx, 0);
    call_frame_t *frame = ctx->call_ctx;
    jsdisp_t *dispex;
    HRESULT hres;

    TRACE("%d\n", func_idx);

    hres = create_source_function(ctx, frame->bytecode, frame->function->funcs+func_idx,
            frame->scope, &dispex);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, jsval_obj(dispex));
}