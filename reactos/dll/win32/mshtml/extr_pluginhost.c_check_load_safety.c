#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct CONFIRMSAFETY {int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  pUnk; int /*<<< orphan*/  clsid; } ;
typedef  int /*<<< orphan*/  cs ;
struct TYPE_5__ {TYPE_1__* doc; int /*<<< orphan*/  plugin_unk; int /*<<< orphan*/  clsid; } ;
struct TYPE_4__ {int /*<<< orphan*/  IInternetHostSecurityManager_iface; } ;
typedef  TYPE_2__ PluginHost ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIRMSAFETYACTION_LOADOBJECT ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  GUID_CUSTOM_CONFIRMOBJECTSAFETY ; 
 int /*<<< orphan*/  IInternetHostSecurityManager_QueryCustomPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ URLPOLICY_ALLOW ; 

__attribute__((used)) static BOOL check_load_safety(PluginHost *host)
{
    DWORD policy_size, policy;
    struct CONFIRMSAFETY cs;
    BYTE *ppolicy;
    HRESULT hres;

    cs.clsid = host->clsid;
    cs.pUnk = host->plugin_unk;
    cs.dwFlags = CONFIRMSAFETYACTION_LOADOBJECT;

    hres = IInternetHostSecurityManager_QueryCustomPolicy(&host->doc->IInternetHostSecurityManager_iface,
            &GUID_CUSTOM_CONFIRMOBJECTSAFETY, &ppolicy, &policy_size, (BYTE*)&cs, sizeof(cs), 0);
    if(FAILED(hres))
        return FALSE;

    policy = *(DWORD*)ppolicy;
    CoTaskMemFree(ppolicy);
    return policy == URLPOLICY_ALLOW;
}