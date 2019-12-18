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
struct TYPE_4__ {int /*<<< orphan*/  IPropertySetStorage_iface; int /*<<< orphan*/  IPersistFile_iface; int /*<<< orphan*/  IUniformResourceLocatorW_iface; int /*<<< orphan*/  IUniformResourceLocatorA_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__ InternetShortcut ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IID_IPersistFile ; 
 int /*<<< orphan*/  IID_IPropertySetStorage ; 
 int /*<<< orphan*/  IID_IShellLinkA ; 
 int /*<<< orphan*/  IID_IShellLinkW ; 
 int /*<<< orphan*/  IID_IUniformResourceLocatorA ; 
 int /*<<< orphan*/  IID_IUniformResourceLocatorW ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT Unknown_QueryInterface(InternetShortcut *This, REFIID riid, PVOID *ppvObject)
{
    TRACE("(%p, %s, %p)\n", This, debugstr_guid(riid), ppvObject);
    *ppvObject = NULL;
    if (IsEqualGUID(&IID_IUnknown, riid))
        *ppvObject = &This->IUniformResourceLocatorA_iface;
    else if (IsEqualGUID(&IID_IUniformResourceLocatorA, riid))
        *ppvObject = &This->IUniformResourceLocatorA_iface;
    else if (IsEqualGUID(&IID_IUniformResourceLocatorW, riid))
        *ppvObject = &This->IUniformResourceLocatorW_iface;
    else if (IsEqualGUID(&IID_IPersistFile, riid))
        *ppvObject = &This->IPersistFile_iface;
    else if (IsEqualGUID(&IID_IPropertySetStorage, riid))
        *ppvObject = &This->IPropertySetStorage_iface;
    else if (IsEqualGUID(&IID_IShellLinkA, riid))
    {
        FIXME("The IShellLinkA interface is not yet supported by InternetShortcut\n");
        return E_NOINTERFACE;
    }
    else if (IsEqualGUID(&IID_IShellLinkW, riid))
    {
        FIXME("The IShellLinkW interface is not yet supported by InternetShortcut\n");
        return E_NOINTERFACE;
    }
    else
    {
        FIXME("Interface with GUID %s not yet implemented by InternetShortcut\n", debugstr_guid(riid));
        return E_NOINTERFACE;
    }
    IUnknown_AddRef((IUnknown*)*ppvObject);
    return S_OK;
}