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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 scalar_t__ get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_null (int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_define_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/ * to_jsdisp (scalar_t__) ; 

__attribute__((used)) static HRESULT Object_create(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags,
                             unsigned argc, jsval_t *argv, jsval_t *r)
{
    jsdisp_t *proto = NULL, *obj;
    HRESULT hres;

    if(!argc || (!is_object_instance(argv[0]) && !is_null(argv[0]))) {
        FIXME("Invalid arg\n");
        return E_INVALIDARG;
    }

    TRACE("(%s)\n", debugstr_jsval(argv[0]));

    if(argc && is_object_instance(argv[0])) {
        if(get_object(argv[0]))
            proto = to_jsdisp(get_object(argv[0]));
        if(!proto) {
            FIXME("Non-JS prototype\n");
            return E_NOTIMPL;
        }
    }else if(!is_null(argv[0])) {
        FIXME("Invalid arg %s\n", debugstr_jsval(argc ? argv[0] : jsval_undefined()));
        return E_INVALIDARG;
    }

    hres = create_dispex(ctx, NULL, proto, &obj);
    if(FAILED(hres))
        return hres;

    if(argc >= 2 && !is_undefined(argv[1]))
        hres = jsdisp_define_properties(ctx, obj, argv[1]);

    if(SUCCEEDED(hres) && r)
        *r = jsval_obj(obj);
    else
        jsdisp_release(obj);
    return hres;
}