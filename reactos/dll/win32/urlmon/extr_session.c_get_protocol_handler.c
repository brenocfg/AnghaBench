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
struct TYPE_3__ {int /*<<< orphan*/  clsid; int /*<<< orphan*/ * cf; } ;
typedef  TYPE_1__ name_space ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IClassFactory_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_GetSchemeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysStringLen (int /*<<< orphan*/ ) ; 
 TYPE_1__* find_name_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_protocol_cf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  session_cs ; 

HRESULT get_protocol_handler(IUri *uri, CLSID *clsid, IClassFactory **ret)
{
    name_space *ns;
    BSTR scheme;
    HRESULT hres;

    *ret = NULL;

    /* FIXME: Avoid GetSchemeName call for known schemes */
    hres = IUri_GetSchemeName(uri, &scheme);
    if(FAILED(hres))
        return hres;

    EnterCriticalSection(&session_cs);

    ns = find_name_space(scheme);
    if(ns) {
        *ret = ns->cf;
        IClassFactory_AddRef(*ret);
        if(clsid)
            *clsid = ns->clsid;
    }

    LeaveCriticalSection(&session_cs);

    hres = *ret ? S_OK : get_protocol_cf(scheme, SysStringLen(scheme), clsid, ret);
    SysFreeString(scheme);
    return hres;
}