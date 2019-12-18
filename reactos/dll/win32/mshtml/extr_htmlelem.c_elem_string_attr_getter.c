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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  scalar_t__ WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  nselem; } ;
typedef  scalar_t__ PRUnichar ;
typedef  TYPE_1__ HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SysAllocString (scalar_t__ const*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__ const*) ; 
 int /*<<< orphan*/  get_elem_attr_value (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ *,scalar_t__ const**) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 

HRESULT elem_string_attr_getter(HTMLElement *elem, const WCHAR *name, BOOL use_null, BSTR *p)
{
    const PRUnichar *val;
    nsAString val_str;
    nsresult nsres;
    HRESULT hres = S_OK;

    nsres = get_elem_attr_value(elem->nselem, name, &val_str, &val);
    if(NS_FAILED(nsres))
        return E_FAIL;

    TRACE("%s: returning %s\n", debugstr_w(name), debugstr_w(val));

    if(*val || !use_null) {
        *p = SysAllocString(val);
        if(!*p)
            hres = E_OUTOFMEMORY;
    }else {
        *p = NULL;
    }
    nsAString_Finish(&val_str);
    return hres;
}