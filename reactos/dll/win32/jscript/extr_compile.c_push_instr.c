#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsop_t ;
struct TYPE_8__ {int /*<<< orphan*/  op; } ;
typedef  TYPE_2__ instr_t ;
struct TYPE_9__ {size_t code_size; size_t code_off; TYPE_1__* code; } ;
typedef  TYPE_3__ compiler_ctx_t ;
struct TYPE_7__ {TYPE_2__* instrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* heap_realloc (TYPE_2__*,int) ; 

__attribute__((used)) static unsigned push_instr(compiler_ctx_t *ctx, jsop_t op)
{
    assert(ctx->code_size >= ctx->code_off);

    if(ctx->code_size == ctx->code_off) {
        instr_t *new_instrs;

        new_instrs = heap_realloc(ctx->code->instrs, ctx->code_size*2*sizeof(instr_t));
        if(!new_instrs)
            return 0;

        ctx->code->instrs = new_instrs;
        ctx->code_size *= 2;
    }

    ctx->code->instrs[ctx->code_off].op = op;
    return ctx->code_off++;
}