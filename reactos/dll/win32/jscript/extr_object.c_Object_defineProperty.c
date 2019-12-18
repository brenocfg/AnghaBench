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
typedef  int /*<<< orphan*/  property_desc_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  JS_E_OBJECT_EXPECTED ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_define_property (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  release_property_descriptor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_property_descriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Object_defineProperty(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags,
                                     unsigned argc, jsval_t *argv, jsval_t *r)
{
    property_desc_t prop_desc;
    jsdisp_t *obj, *attr_obj;
    const WCHAR *name;
    jsstr_t *name_str;
    HRESULT hres;

    TRACE("\n");

    if(argc < 1 || !is_object_instance(argv[0]))
        return throw_type_error(ctx, JS_E_OBJECT_EXPECTED, NULL);
    obj = to_jsdisp(get_object(argv[0]));
    if(!obj) {
        FIXME("not implemented non-JS object\n");
        return E_NOTIMPL;
    }

    hres = to_flat_string(ctx, argc >= 2 ? argv[1] : jsval_undefined(), &name_str, &name);
    if(FAILED(hres))
        return hres;

    if(argc >= 3 && is_object_instance(argv[2])) {
        attr_obj = to_jsdisp(get_object(argv[2]));
        if(attr_obj) {
            hres = to_property_descriptor(ctx, attr_obj, &prop_desc);
        }else {
            FIXME("not implemented non-JS object\n");
            hres = E_NOTIMPL;
        }
    }else {
        hres = throw_type_error(ctx, JS_E_OBJECT_EXPECTED, NULL);
    }
    jsstr_release(name_str);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_property(obj, name, &prop_desc);
    release_property_descriptor(&prop_desc);
    if(SUCCEEDED(hres) && r)
        *r = jsval_obj(jsdisp_addref(obj));
    return hres;
}