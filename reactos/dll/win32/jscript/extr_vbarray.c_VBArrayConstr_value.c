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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int WORD ;
struct TYPE_3__ {int /*<<< orphan*/  dispex; int /*<<< orphan*/  safearray; } ;
typedef  TYPE_1__ VBArrayInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
#define  DISPATCH_CONSTRUCT 129 
#define  DISPATCH_METHOD 128 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  JS_E_VBARRAY_EXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SafeArrayCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int VT_ARRAY ; 
 int VT_VARIANT ; 
 int /*<<< orphan*/  V_ARRAY (int /*<<< orphan*/ ) ; 
 int V_VT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_vbarray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  get_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT VBArrayConstr_value(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    VBArrayInstance *vbarray;
    HRESULT hres;

    TRACE("\n");

    switch(flags) {
    case DISPATCH_METHOD:
        if(argc<1 || !is_variant(argv[0]) || V_VT(get_variant(argv[0])) != (VT_ARRAY|VT_VARIANT))
            return throw_type_error(ctx, JS_E_VBARRAY_EXPECTED, NULL);

        return jsval_copy(argv[0], r);

    case DISPATCH_CONSTRUCT:
        if(argc<1 || !is_variant(argv[0]) || V_VT(get_variant(argv[0])) != (VT_ARRAY|VT_VARIANT))
            return throw_type_error(ctx, JS_E_VBARRAY_EXPECTED, NULL);

        hres = alloc_vbarray(ctx, NULL, &vbarray);
        if(FAILED(hres))
            return hres;

        hres = SafeArrayCopy(V_ARRAY(get_variant(argv[0])), &vbarray->safearray);
        if(FAILED(hres)) {
            jsdisp_release(&vbarray->dispex);
            return hres;
        }

        *r = jsval_obj(&vbarray->dispex);
        break;

    default:
        FIXME("unimplemented flags: %x\n", flags);
        return E_NOTIMPL;
    }

    return S_OK;
}