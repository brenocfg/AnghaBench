#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* property_list; } ;
typedef  TYPE_1__ property_value_expression_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  value; int /*<<< orphan*/  name; struct TYPE_5__* next; } ;
typedef  TYPE_2__ property_definition_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_new_obj ; 
 int /*<<< orphan*/  OP_obj_prop ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  literal_as_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_str_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_object_literal(compiler_ctx_t *ctx, property_value_expression_t *expr)
{
    property_definition_t *iter;
    jsstr_t *name;
    HRESULT hres;

    if(!push_instr(ctx, OP_new_obj))
        return E_OUTOFMEMORY;

    for(iter = expr->property_list; iter; iter = iter->next) {
        hres = literal_as_string(ctx, iter->name, &name);
        if(FAILED(hres))
            return hres;

        hres = compile_expression(ctx, iter->value, TRUE);
        if(FAILED(hres))
            return hres;

        hres = push_instr_str_uint(ctx, OP_obj_prop, name, iter->type);
        if(FAILED(hres))
            return hres;
    }

    return S_OK;
}