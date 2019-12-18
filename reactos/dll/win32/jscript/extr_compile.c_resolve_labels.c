#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* arg; } ;
struct TYPE_11__ {size_t op; TYPE_3__ u; } ;
typedef  TYPE_4__ instr_t ;
struct TYPE_12__ {int code_off; size_t labels_cnt; size_t* labels; TYPE_1__* code; } ;
typedef  TYPE_5__ compiler_ctx_t ;
struct TYPE_13__ {scalar_t__ arg1_type; scalar_t__ arg2_type; } ;
struct TYPE_9__ {size_t uint; } ;
struct TYPE_8__ {TYPE_4__* instrs; } ;

/* Variables and functions */
 scalar_t__ ARG_ADDR ; 
 size_t LABEL_FLAG ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* instr_info ; 

__attribute__((used)) static void resolve_labels(compiler_ctx_t *ctx, unsigned off)
{
    instr_t *instr;

    for(instr = ctx->code->instrs+off; instr < ctx->code->instrs+ctx->code_off; instr++) {
        if(instr_info[instr->op].arg1_type == ARG_ADDR && (instr->u.arg->uint & LABEL_FLAG)) {
            assert((instr->u.arg->uint & ~LABEL_FLAG) < ctx->labels_cnt);
            instr->u.arg->uint = ctx->labels[instr->u.arg->uint & ~LABEL_FLAG];
        }
        assert(instr_info[instr->op].arg2_type != ARG_ADDR);
    }

    ctx->labels_cnt = 0;
}