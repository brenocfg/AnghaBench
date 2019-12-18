#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  expr; int /*<<< orphan*/  identifier; struct TYPE_3__* next; } ;
typedef  TYPE_1__ variable_declaration_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_assign ; 
 int /*<<< orphan*/  OP_pop ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_identifier_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT compile_variable_list(compiler_ctx_t *ctx, variable_declaration_t *list)
{
    variable_declaration_t *iter;
    HRESULT hres;

    assert(list != NULL);

    for(iter = list; iter; iter = iter->next) {
        if(!iter->expr)
            continue;

        hres = emit_identifier_ref(ctx, iter->identifier, 0);
        if(FAILED(hres))
            return hres;

        hres = compile_expression(ctx, iter->expr, TRUE);
        if(FAILED(hres))
            return hres;

        if(!push_instr(ctx, OP_assign))
            return E_OUTOFMEMORY;

        hres = push_instr_uint(ctx, OP_pop, 1);
        if(FAILED(hres))
            return hres;
    }

    return S_OK;
}