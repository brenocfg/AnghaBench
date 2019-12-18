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
struct TYPE_3__ {int /*<<< orphan*/  IHTMLDOMAttribute_iface; } ;
typedef  scalar_t__ LONG ;
typedef  TYPE_1__ HTMLDOMAttribute ;
typedef  int /*<<< orphan*/  HTMLAttributeCollection ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DispatchEx ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HTMLAttributeCollection_from_DispatchEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLDOMAttribute_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MSHTML_DISPID_CUSTOM_MIN ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_attr_dispid_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  get_domattr (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,TYPE_1__**) ; 

__attribute__((used)) static HRESULT HTMLAttributeCollection_get_dispid(DispatchEx *dispex, BSTR name, DWORD flags, DISPID *dispid)
{
    HTMLAttributeCollection *This = HTMLAttributeCollection_from_DispatchEx(dispex);
    HTMLDOMAttribute *attr;
    LONG pos;
    HRESULT hres;

    TRACE("(%p)->(%s %x %p)\n", This, debugstr_w(name), flags, dispid);

    hres = get_attr_dispid_by_name(This, name, dispid);
    if(FAILED(hres))
        return hres;

    hres = get_domattr(This, *dispid, &pos, &attr);
    if(FAILED(hres))
        return hres;
    IHTMLDOMAttribute_Release(&attr->IHTMLDOMAttribute_iface);

    *dispid = MSHTML_DISPID_CUSTOM_MIN+pos;
    return S_OK;
}