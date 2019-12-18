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
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IActiveScriptSite ; 
 int /*<<< orphan*/  IID_IActiveScriptSiteWindow ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,void**,...) ; 
 int /*<<< orphan*/  script_site ; 
 int /*<<< orphan*/  script_site_window ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT query_interface(REFIID riid, void **ppv)
{
    if(IsEqualGUID(riid, &IID_IUnknown)) {
        TRACE("(IID_IUnknown %p)\n", ppv);
        *ppv = &script_site;
    }else if(IsEqualGUID(riid, &IID_IActiveScriptSite)) {
        TRACE("(IID_IActiveScriptSite %p)\n", ppv);
        *ppv = &script_site;
    }else if(IsEqualGUID(riid, &IID_IActiveScriptSiteWindow)) {
        TRACE("(IID_IActiveScriptSiteWindow %p)\n", ppv);
        *ppv = &script_site_window;
    }else {
        *ppv = NULL;
        TRACE("(%s %p)\n", wine_dbgstr_guid(riid), ppv);
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}