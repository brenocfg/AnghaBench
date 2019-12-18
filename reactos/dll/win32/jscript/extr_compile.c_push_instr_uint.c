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
typedef  int /*<<< orphan*/  jsop_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 unsigned int push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_arg_uint (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static HRESULT push_instr_uint(compiler_ctx_t *ctx, jsop_t op, unsigned arg)
{
    unsigned instr;

    instr = push_instr(ctx, op);
    if(!instr)
        return E_OUTOFMEMORY;

    set_arg_uint(ctx, instr, arg);
    return S_OK;
}