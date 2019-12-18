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
typedef  int /*<<< orphan*/  jsop_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {TYPE_2__* arg; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
struct TYPE_5__ {unsigned int uint; int /*<<< orphan*/ * bstr; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * compiler_alloc_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_3__* instr_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT push_instr_bstr_uint(compiler_ctx_t *ctx, jsop_t op, const WCHAR *arg1, unsigned arg2)
{
    unsigned instr;
    WCHAR *str;

    str = compiler_alloc_bstr(ctx, arg1);
    if(!str)
        return E_OUTOFMEMORY;

    instr = push_instr(ctx, op);
    if(!instr)
        return E_OUTOFMEMORY;

    instr_ptr(ctx, instr)->u.arg[0].bstr = str;
    instr_ptr(ctx, instr)->u.arg[1].uint = arg2;
    return S_OK;
}