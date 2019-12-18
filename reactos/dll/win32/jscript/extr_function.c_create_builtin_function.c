#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  builtin_invoke_t ;
typedef  int /*<<< orphan*/  builtin_info_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  dispex; int /*<<< orphan*/  length; } ;
struct TYPE_4__ {TYPE_1__ function; int /*<<< orphan*/  const* name; int /*<<< orphan*/  proc; } ;
typedef  TYPE_2__ NativeFunction ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NativeFunctionVtbl ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  create_function (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  jsdisp_define_data_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lengthW ; 
 int /*<<< orphan*/  prototypeW ; 

HRESULT create_builtin_function(script_ctx_t *ctx, builtin_invoke_t value_proc, const WCHAR *name,
        const builtin_info_t *builtin_info, DWORD flags, jsdisp_t *prototype, jsdisp_t **ret)
{
    NativeFunction *function;
    HRESULT hres;

    hres = create_function(ctx, builtin_info, &NativeFunctionVtbl, sizeof(NativeFunction), flags, FALSE, NULL, (void**)&function);
    if(FAILED(hres))
        return hres;

    if(builtin_info)
        hres = jsdisp_define_data_property(&function->function.dispex, lengthW, 0,
                                           jsval_number(function->function.length));
    if(SUCCEEDED(hres))
        hres = jsdisp_define_data_property(&function->function.dispex, prototypeW, 0, jsval_obj(prototype));
    if(FAILED(hres)) {
        jsdisp_release(&function->function.dispex);
        return hres;
    }

    function->proc = value_proc;
    function->name = name;

    *ret = &function->function.dispex;
    return S_OK;
}