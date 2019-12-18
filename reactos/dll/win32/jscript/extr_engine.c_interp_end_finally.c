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
struct TYPE_6__ {void* val; } ;
struct TYPE_7__ {TYPE_1__ ei; TYPE_3__* call_ctx; } ;
typedef  TYPE_2__ script_ctx_t ;
typedef  void* jsval_t ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
typedef  TYPE_3__ call_frame_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_EXCEPTION ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bool (void*) ; 
 int /*<<< orphan*/  get_number (void*) ; 
 int /*<<< orphan*/  is_bool (void*) ; 
 int /*<<< orphan*/  is_number (void*) ; 
 void* stack_pop (TYPE_2__*) ; 

__attribute__((used)) static HRESULT interp_end_finally(script_ctx_t *ctx)
{
    call_frame_t *frame = ctx->call_ctx;
    jsval_t v;

    TRACE("\n");

    v = stack_pop(ctx);
    assert(is_bool(v));

    if(!get_bool(v)) {
        TRACE("passing exception\n");

        ctx->ei.val = stack_pop(ctx);
        return DISP_E_EXCEPTION;
    }

    v = stack_pop(ctx);
    assert(is_number(v));
    frame->ip = get_number(v);
    return S_OK;
}