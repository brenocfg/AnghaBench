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
struct TYPE_8__ {TYPE_2__* call_ctx; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_9__ {int /*<<< orphan*/  arguments_obj; int /*<<< orphan*/ * function_instance; struct TYPE_9__* prev_frame; } ;
typedef  TYPE_2__ call_frame_t ;
struct TYPE_10__ {int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ FunctionInstance ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_3__* function_from_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_addref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_null () ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_arguments_object (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static HRESULT Function_get_arguments(script_ctx_t *ctx, jsdisp_t *jsthis, jsval_t *r)
{
    FunctionInstance *function = function_from_jsdisp(jsthis);
    call_frame_t *frame;
    HRESULT hres;

    TRACE("\n");

    for(frame = ctx->call_ctx; frame; frame = frame->prev_frame) {
        if(frame->function_instance == &function->dispex) {
            if(!frame->arguments_obj) {
                hres = setup_arguments_object(ctx, frame);
                if(FAILED(hres))
                    return hres;
            }
            *r = jsval_obj(jsdisp_addref(frame->arguments_obj));
            return S_OK;
        }
    }

    *r = jsval_null();
    return S_OK;
}