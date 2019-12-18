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
typedef  int WCHAR ;
struct TYPE_3__ {int len; int /*<<< orphan*/ * elems; } ;
typedef  TYPE_1__ HTMLElementCollection ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DispatchEx ;
typedef  int DWORD ;
typedef  scalar_t__ DISPID ;
typedef  int* BSTR ;

/* Variables and functions */
 scalar_t__ DISPID_ELEMCOL_0 ; 
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 TYPE_1__* impl_from_DispatchEx (int /*<<< orphan*/ *) ; 
 scalar_t__ is_elem_id (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ is_elem_name (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ isdigitW (int) ; 

__attribute__((used)) static HRESULT HTMLElementCollection_get_dispid(DispatchEx *dispex, BSTR name, DWORD flags, DISPID *dispid)
{
    HTMLElementCollection *This = impl_from_DispatchEx(dispex);
    WCHAR *ptr;
    DWORD idx=0;

    if(!*name)
        return DISP_E_UNKNOWNNAME;

    for(ptr = name; *ptr && isdigitW(*ptr); ptr++)
        idx = idx*10 + (*ptr-'0');

    if(*ptr) {
        /* the name contains alpha characters, so search by name & id */
        for(idx = 0; idx < This->len; ++idx) {
            if(is_elem_id(This->elems[idx], name) ||
                    is_elem_name(This->elems[idx], name))
                break;
        }
    }

    if(idx >= This->len)
        return DISP_E_UNKNOWNNAME;

    *dispid = DISPID_ELEMCOL_0 + idx;
    TRACE("ret %x\n", *dispid);
    return S_OK;
}