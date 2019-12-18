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
struct TYPE_8__ {int /*<<< orphan*/ * function_constr; } ;
typedef  TYPE_2__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  float WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  dispex; } ;
struct TYPE_9__ {float const* name; TYPE_1__ function; int /*<<< orphan*/  proc; } ;
typedef  TYPE_3__ NativeFunction ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionConstr_value ; 
 int /*<<< orphan*/  FunctionInst_info ; 
 int /*<<< orphan*/  FunctionProt_value ; 
 int /*<<< orphan*/  Function_info ; 
 int /*<<< orphan*/  NativeFunctionVtbl ; 
 int PROPF_CONSTR ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_function (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  jsdisp_define_data_property (int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 float const* prototypeW ; 
 int /*<<< orphan*/  set_constructor_prop (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT init_function_constr(script_ctx_t *ctx, jsdisp_t *object_prototype)
{
    NativeFunction *prot, *constr;
    HRESULT hres;

    static const WCHAR FunctionW[] = {'F','u','n','c','t','i','o','n',0};

    hres = create_function(ctx, &Function_info, &NativeFunctionVtbl, sizeof(NativeFunction), PROPF_CONSTR,
                           TRUE, object_prototype, (void**)&prot);
    if(FAILED(hres))
        return hres;

    prot->proc = FunctionProt_value;
    prot->name = prototypeW;

    hres = create_function(ctx, &FunctionInst_info, &NativeFunctionVtbl, sizeof(NativeFunction), PROPF_CONSTR|1,
                           TRUE, &prot->function.dispex, (void**)&constr);
    if(SUCCEEDED(hres)) {
        constr->proc = FunctionConstr_value;
        constr->name = FunctionW;
        hres = jsdisp_define_data_property(&constr->function.dispex, prototypeW, 0, jsval_obj(&prot->function.dispex));
        if(SUCCEEDED(hres))
            hres = set_constructor_prop(ctx, &constr->function.dispex, &prot->function.dispex);
        if(FAILED(hres))
            jsdisp_release(&constr->function.dispex);
    }
    jsdisp_release(&prot->function.dispex);
    if(FAILED(hres))
        return hres;

    ctx->function_constr = &constr->function.dispex;
    return S_OK;
}