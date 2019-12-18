#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  compile_ctx_t ;
struct TYPE_5__ {unsigned int uint; } ;
struct TYPE_4__ {unsigned int uint; } ;
struct TYPE_6__ {TYPE_2__ arg2; TYPE_1__ arg1; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_catch ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* instr_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int stack_offset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL emit_catch_jmp(compile_ctx_t *ctx, unsigned stack_off, unsigned code_off)
{
    unsigned code;

    code = push_instr(ctx, OP_catch);
    if(!code)
        return FALSE;

    instr_ptr(ctx, code)->arg1.uint = code_off;
    instr_ptr(ctx, code)->arg2.uint = stack_off + stack_offset(ctx);
    return TRUE;
}