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
typedef  int /*<<< orphan*/  compile_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_jmp ; 
 int /*<<< orphan*/  OP_pop ; 
 int /*<<< orphan*/  push_instr_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  push_instr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int stack_offset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT exit_label(compile_ctx_t *ctx, unsigned jmp_label)
{
    unsigned pop_cnt = stack_offset(ctx);

    if(pop_cnt) {
        HRESULT hres;

        hres = push_instr_uint(ctx, OP_pop, pop_cnt);
        if(FAILED(hres))
            return hres;
    }

    return push_instr_addr(ctx, OP_jmp, jmp_label);
}