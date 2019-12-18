#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int host_global; int /*<<< orphan*/ * stack; int /*<<< orphan*/  global; TYPE_4__* call_ctx; } ;
typedef  TYPE_3__ script_ctx_t ;
struct TYPE_10__ {unsigned int this_obj; unsigned int argc; int flags; TYPE_2__* function; TYPE_1__* base_scope; struct TYPE_10__* prev_frame; } ;
typedef  TYPE_4__ call_frame_t ;
struct TYPE_8__ {unsigned int param_cnt; scalar_t__* params; scalar_t__ name; } ;
struct TYPE_7__ {scalar_t__ frame; } ;

/* Variables and functions */
 int EXEC_RETURN_TO_INTERP ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 char* debugstr_w (scalar_t__) ; 
 size_t local_off (TYPE_4__*,unsigned int) ; 
 unsigned int to_disp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_backtrace(script_ctx_t *ctx)
{
    unsigned depth = 0, i;
    call_frame_t *frame;

    for(frame = ctx->call_ctx; frame; frame = frame->prev_frame) {
        WARN("%u\t", depth);
        depth++;

        if(frame->this_obj && frame->this_obj != to_disp(ctx->global) && frame->this_obj != ctx->host_global)
            WARN("%p->", frame->this_obj);
        WARN("%s(", frame->function->name ? debugstr_w(frame->function->name) : "[unnamed]");
        if(frame->base_scope && frame->base_scope->frame) {
            for(i=0; i < frame->argc; i++) {
                if(i < frame->function->param_cnt)
                    WARN("%s%s=%s", i ? ", " : "", debugstr_w(frame->function->params[i]),
                         debugstr_jsval(ctx->stack[local_off(frame, -i-1)]));
                else
                    WARN("%s%s", i ? ", " : "", debugstr_jsval(ctx->stack[local_off(frame, -i-1)]));
            }
        }else {
            WARN("[detached frame]");
        }
        WARN(")\n");

        if(!(frame->flags & EXEC_RETURN_TO_INTERP)) {
            WARN("%u\t[native code]\n", depth);
            depth++;
        }
    }
}