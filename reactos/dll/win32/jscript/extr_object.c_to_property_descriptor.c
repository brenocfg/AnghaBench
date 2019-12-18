#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_5__ {int mask; int flags; void* explicit_value; void* explicit_setter; void* explicit_getter; void* setter; void* getter; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ property_desc_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  JS_E_INVALID_WRITABLE_PROP_DESC ; 
 int /*<<< orphan*/  JS_E_PROP_DESC_MISMATCH ; 
 int PROPF_CONFIGURABLE ; 
 int PROPF_ENUMERABLE ; 
 int PROPF_WRITABLE ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 void* TRUE ; 
 int /*<<< orphan*/  configurableW ; 
 int /*<<< orphan*/  enumerableW ; 
 int /*<<< orphan*/  getW ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_undefined (int /*<<< orphan*/ ) ; 
 scalar_t__ jsdisp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_propget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_property_descriptor (TYPE_1__*) ; 
 int /*<<< orphan*/  setW ; 
 scalar_t__ throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ to_boolean (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valueW ; 
 int /*<<< orphan*/  writableW ; 

__attribute__((used)) static HRESULT to_property_descriptor(script_ctx_t *ctx, jsdisp_t *attr_obj, property_desc_t *desc)
{
    DISPID id;
    jsval_t v;
    BOOL b;
    HRESULT hres;

    memset(desc, 0, sizeof(*desc));
    desc->value = jsval_undefined();

    hres = jsdisp_get_id(attr_obj, enumerableW, 0, &id);
    if(SUCCEEDED(hres)) {
        desc->mask |= PROPF_ENUMERABLE;
        hres = jsdisp_propget(attr_obj, id, &v);
        if(FAILED(hres))
            return hres;
        hres = to_boolean(v, &b);
        jsval_release(v);
        if(FAILED(hres))
            return hres;
        if(b)
            desc->flags |= PROPF_ENUMERABLE;
    }else if(hres != DISP_E_UNKNOWNNAME) {
        return hres;
    }

    hres = jsdisp_get_id(attr_obj, configurableW, 0, &id);
    if(SUCCEEDED(hres)) {
        desc->mask |= PROPF_CONFIGURABLE;
        hres = jsdisp_propget(attr_obj, id, &v);
        if(FAILED(hres))
            return hres;
        hres = to_boolean(v, &b);
        jsval_release(v);
        if(FAILED(hres))
            return hres;
        if(b)
            desc->flags |= PROPF_CONFIGURABLE;
    }else if(hres != DISP_E_UNKNOWNNAME) {
        return hres;
    }

    hres = jsdisp_get_id(attr_obj, valueW, 0, &id);
    if(SUCCEEDED(hres)) {
        hres = jsdisp_propget(attr_obj, id, &desc->value);
        if(FAILED(hres))
            return hres;
        desc->explicit_value = TRUE;
    }else if(hres != DISP_E_UNKNOWNNAME) {
        return hres;
    }

    hres = jsdisp_get_id(attr_obj, writableW, 0, &id);
    if(SUCCEEDED(hres)) {
        desc->mask |= PROPF_WRITABLE;
        hres = jsdisp_propget(attr_obj, id, &v);
        if(SUCCEEDED(hres)) {
            hres = to_boolean(v, &b);
            jsval_release(v);
            if(SUCCEEDED(hres) && b)
                desc->flags |= PROPF_WRITABLE;
        }
    }else if(hres == DISP_E_UNKNOWNNAME) {
        hres = S_OK;
    }
    if(FAILED(hres)) {
        release_property_descriptor(desc);
        return hres;
    }

    hres = jsdisp_get_id(attr_obj, getW, 0, &id);
    if(SUCCEEDED(hres)) {
        desc->explicit_getter = TRUE;
        hres = jsdisp_propget(attr_obj, id, &v);
        if(SUCCEEDED(hres) && !is_undefined(v)) {
            if(!is_object_instance(v)) {
                FIXME("getter is not an object\n");
                jsval_release(v);
                hres = E_FAIL;
            }else {
                /* FIXME: Check IsCallable */
                desc->getter = to_jsdisp(get_object(v));
                if(!desc->getter)
                    FIXME("getter is not JS object\n");
            }
        }
    }else if(hres == DISP_E_UNKNOWNNAME) {
        hres = S_OK;
    }
    if(FAILED(hres)) {
        release_property_descriptor(desc);
        return hres;
    }

    hres = jsdisp_get_id(attr_obj, setW, 0, &id);
    if(SUCCEEDED(hres)) {
        desc->explicit_setter = TRUE;
        hres = jsdisp_propget(attr_obj, id, &v);
        if(SUCCEEDED(hres) && !is_undefined(v)) {
            if(!is_object_instance(v)) {
                FIXME("setter is not an object\n");
                jsval_release(v);
                hres = E_FAIL;
            }else {
                /* FIXME: Check IsCallable */
                desc->setter = to_jsdisp(get_object(v));
                if(!desc->setter)
                    FIXME("setter is not JS object\n");
            }
        }
    }else if(hres == DISP_E_UNKNOWNNAME) {
        hres = S_OK;
    }
    if(FAILED(hres)) {
        release_property_descriptor(desc);
        return hres;
    }

    if(desc->explicit_getter || desc->explicit_setter) {
        if(desc->explicit_value)
            hres = throw_type_error(ctx, JS_E_PROP_DESC_MISMATCH, NULL);
        else if(desc->mask & PROPF_WRITABLE)
            hres = throw_type_error(ctx, JS_E_INVALID_WRITABLE_PROP_DESC, NULL);
    }

    if(FAILED(hres))
        release_property_descriptor(desc);
    return hres;
}