#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  property_desc_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_9__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
typedef  TYPE_1__ jsdisp_t ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISPID_STARTENUM ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IDispatchEx_GetMemberName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_define_property (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_next_prop (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_propget (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_release (TYPE_1__*) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_property_descriptor (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  to_property_descriptor (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT jsdisp_define_properties(script_ctx_t *ctx, jsdisp_t *obj, jsval_t list_val)
{
    DISPID id = DISPID_STARTENUM;
    property_desc_t prop_desc;
    IDispatch *list_disp;
    jsdisp_t *list_obj, *desc_obj;
    jsval_t desc_val;
    BSTR name;
    HRESULT hres;

    hres = to_object(ctx, list_val, &list_disp);
    if(FAILED(hres))
        return hres;

    if(!(list_obj = to_jsdisp(list_disp))) {
        FIXME("non-JS list obj\n");
        IDispatch_Release(list_disp);
        return E_NOTIMPL;
    }

    while(1) {
        hres = jsdisp_next_prop(list_obj, id, TRUE, &id);
        if(hres != S_OK)
            break;

        hres = jsdisp_propget(list_obj, id, &desc_val);
        if(FAILED(hres))
            break;

        if(!is_object_instance(desc_val) || !get_object(desc_val) || !(desc_obj = to_jsdisp(get_object(desc_val)))) {
            jsval_release(desc_val);
            break;
        }

        hres = to_property_descriptor(ctx, desc_obj, &prop_desc);
        jsdisp_release(desc_obj);
        if(FAILED(hres))
            break;

        hres = IDispatchEx_GetMemberName(&list_obj->IDispatchEx_iface, id, &name);
        if(SUCCEEDED(hres))
            hres = jsdisp_define_property(obj, name, &prop_desc);
        release_property_descriptor(&prop_desc);
        if(FAILED(hres))
            break;
    }

    jsdisp_release(list_obj);
    return FAILED(hres) ? hres : S_OK;
}