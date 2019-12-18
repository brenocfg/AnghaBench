#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  value; int /*<<< orphan*/ * setter; int /*<<< orphan*/ * getter; scalar_t__ explicit_setter; scalar_t__ explicit_getter; } ;
typedef  TYPE_1__ property_desc_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  JS_E_OBJECT_EXPECTED ; 
 int /*<<< orphan*/  PROPF_ALL ; 
 int PROPF_CONFIGURABLE ; 
 int PROPF_ENUMERABLE ; 
 int PROPF_WRITABLE ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  configurableW ; 
 scalar_t__ create_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  enumerableW ; 
 int /*<<< orphan*/  getW ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 scalar_t__ jsdisp_define_data_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jsdisp_get_own_property (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ jsdisp_propput_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_bool (int) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  release_property_descriptor (TYPE_1__*) ; 
 int /*<<< orphan*/  setW ; 
 scalar_t__ throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valueW ; 
 int /*<<< orphan*/  writableW ; 

__attribute__((used)) static HRESULT Object_getOwnPropertyDescriptor(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags,
                                               unsigned argc, jsval_t *argv, jsval_t *r)
{
    property_desc_t prop_desc;
    jsdisp_t *obj, *desc_obj;
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

    hres = jsdisp_get_own_property(obj, name, FALSE, &prop_desc);
    jsstr_release(name_str);
    if(hres == DISP_E_UNKNOWNNAME) {
        if(r) *r = jsval_undefined();
        return S_OK;
    }
    if(FAILED(hres))
        return hres;

    hres = create_object(ctx, NULL, &desc_obj);
    if(FAILED(hres))
        return hres;

    if(prop_desc.explicit_getter || prop_desc.explicit_setter) {
        hres = jsdisp_define_data_property(desc_obj, getW, PROPF_ALL,
                prop_desc.getter ? jsval_obj(prop_desc.getter) : jsval_undefined());
        if(SUCCEEDED(hres))
            hres = jsdisp_define_data_property(desc_obj, setW, PROPF_ALL,
                    prop_desc.setter ? jsval_obj(prop_desc.setter) : jsval_undefined());
    }else {
        hres = jsdisp_propput_name(desc_obj, valueW, prop_desc.value);
        if(SUCCEEDED(hres))
            hres = jsdisp_define_data_property(desc_obj, writableW, PROPF_ALL,
                    jsval_bool(!!(prop_desc.flags & PROPF_WRITABLE)));
    }
    if(SUCCEEDED(hres))
        hres = jsdisp_define_data_property(desc_obj, enumerableW, PROPF_ALL,
                jsval_bool(!!(prop_desc.flags & PROPF_ENUMERABLE)));
    if(SUCCEEDED(hres))
        hres = jsdisp_define_data_property(desc_obj, configurableW, PROPF_ALL,
                jsval_bool(!!(prop_desc.flags & PROPF_CONFIGURABLE)));

    release_property_descriptor(&prop_desc);
    if(SUCCEEDED(hres) && r)
        *r = jsval_obj(desc_obj);
    else
        jsdisp_release(desc_obj);
    return hres;
}