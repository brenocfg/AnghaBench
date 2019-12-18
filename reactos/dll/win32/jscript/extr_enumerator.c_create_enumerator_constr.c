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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ EnumeratorInstance ;

/* Variables and functions */
 int /*<<< orphan*/  EnumeratorConstr_info ; 
 int /*<<< orphan*/  EnumeratorConstr_value ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PROPF_CONSTR ; 
 int /*<<< orphan*/  alloc_enumerator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  create_builtin_constructor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 

HRESULT create_enumerator_constr(script_ctx_t *ctx, jsdisp_t *object_prototype, jsdisp_t **ret)
{
    EnumeratorInstance *enumerator;
    HRESULT hres;
    static const WCHAR EnumeratorW[] = {'E','n','u','m','e','r','a','t','o','r',0};

    hres = alloc_enumerator(ctx, object_prototype, &enumerator);
    if(FAILED(hres))
        return hres;

    hres = create_builtin_constructor(ctx, EnumeratorConstr_value,
                                     EnumeratorW, &EnumeratorConstr_info,
                                     PROPF_CONSTR|7, &enumerator->dispex, ret);
    jsdisp_release(&enumerator->dispex);

    return hres;
}