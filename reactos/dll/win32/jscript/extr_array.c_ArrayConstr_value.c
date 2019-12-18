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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  unsigned int DWORD ;

/* Variables and functions */
#define  DISPATCH_CONSTRUCT 129 
#define  DISPATCH_METHOD 128 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  JS_E_INVALID_LENGTH ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  create_array (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ **) ; 
 double get_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_int32 (double) ; 
 int /*<<< orphan*/  is_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propput_idx (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_range_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT ArrayConstr_value(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsdisp_t *obj;
    DWORD i;
    HRESULT hres;

    TRACE("\n");

    switch(flags) {
    case DISPATCH_METHOD:
    case DISPATCH_CONSTRUCT: {
        if(argc == 1 && is_number(argv[0])) {
            double n = get_number(argv[0]);

            if(n < 0 || !is_int32(n))
                return throw_range_error(ctx, JS_E_INVALID_LENGTH, NULL);

            hres = create_array(ctx, n, &obj);
            if(FAILED(hres))
                return hres;

            *r = jsval_obj(obj);
            return S_OK;
        }

        hres = create_array(ctx, argc, &obj);
        if(FAILED(hres))
            return hres;

        for(i=0; i < argc; i++) {
            hres = jsdisp_propput_idx(obj, i, argv[i]);
            if(FAILED(hres))
                break;
        }
        if(FAILED(hres)) {
            jsdisp_release(obj);
            return hres;
        }

        *r = jsval_obj(obj);
        break;
    }
    default:
        FIXME("unimplemented flags: %x\n", flags);
        return E_NOTIMPL;
    }

    return S_OK;
}