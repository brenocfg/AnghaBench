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
struct TYPE_3__ {int member_0; int /*<<< orphan*/ * setter; void* explicit_setter; int /*<<< orphan*/ * getter; void* explicit_getter; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; } ;
typedef  TYPE_1__ property_desc_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 unsigned int PROPERTY_DEFINITION_GETTER ; 
 unsigned int PROPERTY_DEFINITION_VALUE ; 
 int PROPF_CONFIGURABLE ; 
 int PROPF_ENUMERABLE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/ * as_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_jsstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_op_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int get_op_uint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_define_property (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  jsdisp_propput_name (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_flatten (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_top (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_obj_prop(script_ctx_t *ctx)
{
    jsstr_t *name_arg = get_op_str(ctx, 0);
    unsigned type = get_op_uint(ctx, 1);
    const WCHAR *name;
    jsdisp_t *obj;
    jsval_t val;
    HRESULT hres;

    TRACE("%s\n", debugstr_jsstr(name_arg));

    val = stack_pop(ctx);

    /* FIXME: we should pass it as jsstr_t */
    name = jsstr_flatten(name_arg);

    assert(is_object_instance(stack_top(ctx)));
    obj = as_jsdisp(get_object(stack_top(ctx)));

    if(type == PROPERTY_DEFINITION_VALUE) {
        hres = jsdisp_propput_name(obj, name, val);
    }else {
        property_desc_t desc = {PROPF_ENUMERABLE | PROPF_CONFIGURABLE};
        jsdisp_t *func;

        assert(is_object_instance(val));
        func = iface_to_jsdisp(get_object(val));

        desc.mask = desc.flags;
        if(type == PROPERTY_DEFINITION_GETTER) {
            desc.explicit_getter = TRUE;
            desc.getter = func;
        }else {
            desc.explicit_setter = TRUE;
            desc.setter = func;
        }

        hres = jsdisp_define_property(obj, name, &desc);
        jsdisp_release(func);
    }

    jsval_release(val);
    return hres;
}