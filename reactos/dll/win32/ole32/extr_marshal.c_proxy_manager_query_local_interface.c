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
struct proxy_manager {int /*<<< orphan*/  IClientSecurity_iface; int /*<<< orphan*/  IMarshal_iface; int /*<<< orphan*/  IMultiQI_iface; } ;
struct ifproxy {void* iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IClientSecurity_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClientSecurity ; 
 int /*<<< orphan*/  IID_IMarshal ; 
 int /*<<< orphan*/  IID_IMultiQI ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IMarshal_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMultiQI_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 scalar_t__ proxy_manager_find_ifproxy (struct proxy_manager*,int /*<<< orphan*/ ,struct ifproxy**) ; 

__attribute__((used)) static HRESULT proxy_manager_query_local_interface(struct proxy_manager * This, REFIID riid, void ** ppv)
{
    HRESULT hr;
    struct ifproxy * ifproxy;

    TRACE("%s\n", debugstr_guid(riid));

    if (IsEqualIID(riid, &IID_IUnknown) ||
        IsEqualIID(riid, &IID_IMultiQI))
    {
        *ppv = &This->IMultiQI_iface;
        IMultiQI_AddRef(&This->IMultiQI_iface);
        return S_OK;
    }
    if (IsEqualIID(riid, &IID_IMarshal))
    {
        *ppv = &This->IMarshal_iface;
        IMarshal_AddRef(&This->IMarshal_iface);
        return S_OK;
    }
    if (IsEqualIID(riid, &IID_IClientSecurity))
    {
        *ppv = &This->IClientSecurity_iface;
        IClientSecurity_AddRef(&This->IClientSecurity_iface);
        return S_OK;
    }

    hr = proxy_manager_find_ifproxy(This, riid, &ifproxy);
    if (hr == S_OK)
    {
        *ppv = ifproxy->iface;
        IUnknown_AddRef((IUnknown *)*ppv);
        return S_OK;
    }

    *ppv = NULL;
    return E_NOINTERFACE;
}