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
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  JSCLASS_ARRAY ; 
 int /*<<< orphan*/  array_from_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  concat_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ *) ; 
 scalar_t__ is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propput_idx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT concat_obj(jsdisp_t *array, IDispatch *obj, DWORD *len)
{
    jsdisp_t *jsobj;
    HRESULT hres;

    jsobj = iface_to_jsdisp(obj);
    if(jsobj) {
        if(is_class(jsobj, JSCLASS_ARRAY)) {
            hres = concat_array(array, array_from_jsdisp(jsobj), len);
            jsdisp_release(jsobj);
            return hres;
        }
        jsdisp_release(jsobj);
    }

    return jsdisp_propput_idx(array, (*len)++, jsval_disp(obj));
}