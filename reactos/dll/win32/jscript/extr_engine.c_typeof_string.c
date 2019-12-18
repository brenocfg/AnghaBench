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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSCLASS_FUNCTION ; 
#define  JSV_BOOL 134 
#define  JSV_NULL 133 
#define  JSV_NUMBER 132 
#define  JSV_OBJECT 131 
#define  JSV_STRING 130 
#define  JSV_UNDEFINED 129 
#define  JSV_VARIANT 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * booleanW ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * functionW ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int jsval_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * numberW ; 
 int /*<<< orphan*/ * objectW ; 
 int /*<<< orphan*/ * stringW ; 
 int /*<<< orphan*/ * undefinedW ; 

__attribute__((used)) static HRESULT typeof_string(jsval_t v, const WCHAR **ret)
{
    switch(jsval_type(v)) {
    case JSV_UNDEFINED:
        *ret = undefinedW;
        break;
    case JSV_NULL:
        *ret = objectW;
        break;
    case JSV_OBJECT: {
        jsdisp_t *dispex;

        if(get_object(v) && (dispex = iface_to_jsdisp(get_object(v)))) {
            *ret = is_class(dispex, JSCLASS_FUNCTION) ? functionW : objectW;
            jsdisp_release(dispex);
        }else {
            *ret = objectW;
        }
        break;
    }
    case JSV_STRING:
        *ret = stringW;
        break;
    case JSV_NUMBER:
        *ret = numberW;
        break;
    case JSV_BOOL:
        *ret = booleanW;
        break;
    case JSV_VARIANT:
        FIXME("unhandled variant %s\n", debugstr_variant(get_variant(v)));
        return E_NOTIMPL;
    }

    return S_OK;
}