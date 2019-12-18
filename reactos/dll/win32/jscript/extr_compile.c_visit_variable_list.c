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
struct TYPE_3__ {scalar_t__ expr; int /*<<< orphan*/  identifier; struct TYPE_3__* next; } ;
typedef  TYPE_1__ variable_declaration_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  alloc_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visit_expression (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static HRESULT visit_variable_list(compiler_ctx_t *ctx, variable_declaration_t *list)
{
    variable_declaration_t *iter;
    HRESULT hres;

    for(iter = list; iter; iter = iter->next) {
        if(!alloc_variable(ctx, iter->identifier))
            return E_OUTOFMEMORY;

        if(iter->expr) {
            hres = visit_expression(ctx, iter->expr);
            if(FAILED(hres))
                return hres;
        }
    }

    return S_OK;
}