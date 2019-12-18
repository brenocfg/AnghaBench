#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * stack; } ;
typedef  TYPE_4__ script_ctx_t ;
struct TYPE_16__ {scalar_t__ variable_obj; TYPE_3__* function; TYPE_1__* base_scope; int /*<<< orphan*/  arguments_obj; } ;
typedef  TYPE_5__ call_frame_t ;
struct TYPE_14__ {unsigned int locals_cnt; TYPE_2__* locals; } ;
struct TYPE_13__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {scalar_t__ jsobj; TYPE_5__* frame; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jsdisp_propput_name (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t local_off (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_arguments_object (TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static HRESULT detach_variable_object(script_ctx_t *ctx, call_frame_t *frame, BOOL from_release)
{
    unsigned i;
    HRESULT hres;

    if(!frame->base_scope || !frame->base_scope->frame)
        return S_OK;

    TRACE("detaching %p\n", frame);

    assert(frame == frame->base_scope->frame);
    assert(frame->variable_obj == frame->base_scope->jsobj);

    if(!from_release && !frame->arguments_obj) {
        hres = setup_arguments_object(ctx, frame);
        if(FAILED(hres))
            return hres;
    }

    frame->base_scope->frame = NULL;

    for(i = 0; i < frame->function->locals_cnt; i++) {
        hres = jsdisp_propput_name(frame->variable_obj, frame->function->locals[i].name,
                                   ctx->stack[local_off(frame, frame->function->locals[i].ref)]);
        if(FAILED(hres))
            return hres;
    }

    return S_OK;
}