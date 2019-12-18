#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t uint; } ;
struct TYPE_9__ {size_t op; TYPE_2__ arg1; } ;
typedef  TYPE_3__ instr_t ;
struct TYPE_10__ {int instr_cnt; size_t labels_cnt; size_t* labels; TYPE_1__* code; } ;
typedef  TYPE_4__ compile_ctx_t ;
struct TYPE_11__ {scalar_t__ arg1_type; scalar_t__ arg2_type; } ;
struct TYPE_7__ {TYPE_3__* instrs; } ;

/* Variables and functions */
 scalar_t__ ARG_ADDR ; 
 size_t LABEL_FLAG ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__* instr_info ; 

__attribute__((used)) static void resolve_labels(compile_ctx_t *ctx, unsigned off)
{
    instr_t *instr;

    for(instr = ctx->code->instrs+off; instr < ctx->code->instrs+ctx->instr_cnt; instr++) {
        if(instr_info[instr->op].arg1_type == ARG_ADDR && (instr->arg1.uint & LABEL_FLAG)) {
            assert((instr->arg1.uint & ~LABEL_FLAG) < ctx->labels_cnt);
            instr->arg1.uint = ctx->labels[instr->arg1.uint & ~LABEL_FLAG];
        }
        assert(instr_info[instr->op].arg2_type != ARG_ADDR);
    }

    ctx->labels_cnt = 0;
}