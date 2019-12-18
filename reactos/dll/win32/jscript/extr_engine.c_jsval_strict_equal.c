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
typedef  int jsval_type_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
#define  JSV_BOOL 134 
#define  JSV_NULL 133 
#define  JSV_NUMBER 132 
#define  JSV_OBJECT 131 
#define  JSV_STRING 130 
#define  JSV_UNDEFINED 129 
#define  JSV_VARIANT 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  disp_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  get_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 int is_null_instance (int /*<<< orphan*/ ) ; 
 int jsstr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jsval_type (int /*<<< orphan*/ ) ; 

HRESULT jsval_strict_equal(jsval_t lval, jsval_t rval, BOOL *ret)
{
    jsval_type_t type = jsval_type(lval);

    TRACE("\n");

    if(type != jsval_type(rval)) {
        if(is_null_instance(lval))
            *ret = is_null_instance(rval);
        else
            *ret = FALSE;
        return S_OK;
    }

    switch(type) {
    case JSV_UNDEFINED:
    case JSV_NULL:
        *ret = TRUE;
        break;
    case JSV_OBJECT:
        return disp_cmp(get_object(lval), get_object(rval), ret);
    case JSV_STRING:
        *ret = jsstr_eq(get_string(lval), get_string(rval));
        break;
    case JSV_NUMBER:
        *ret = get_number(lval) == get_number(rval);
        break;
    case JSV_BOOL:
        *ret = !get_bool(lval) == !get_bool(rval);
        break;
    case JSV_VARIANT:
        FIXME("VARIANT not implemented\n");
        return E_NOTIMPL;
    }

    return S_OK;
}