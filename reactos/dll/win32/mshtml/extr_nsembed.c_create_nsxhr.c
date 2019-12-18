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
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIXMLHttpRequest ;
typedef  int /*<<< orphan*/  nsIScriptSecurityManager ;
typedef  int /*<<< orphan*/  nsIPrincipal ;
typedef  int /*<<< orphan*/  nsIGlobalObject ;
typedef  int /*<<< orphan*/  nsIDOMWindow ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  IID_nsIGlobalObject ; 
 int /*<<< orphan*/  IID_nsIScriptSecurityManager ; 
 int /*<<< orphan*/  IID_nsIXMLHttpRequest ; 
 scalar_t__ NS_FAILED (scalar_t__) ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  NS_SCRIPTSECURITYMANAGER_CONTRACTID ; 
 int /*<<< orphan*/  NS_XMLHTTPREQUEST_CONTRACTID ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ nsIComponentManager_CreateInstanceByContractID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ nsIDOMWindow_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIGlobalObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIScriptSecurityManager_GetSystemPrincipal (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIScriptSecurityManager_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIServiceManager_GetServiceByContractID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsISupports_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIXMLHttpRequest_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIXMLHttpRequest_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pCompMgr ; 
 int /*<<< orphan*/  pServMgr ; 

nsIXMLHttpRequest *create_nsxhr(nsIDOMWindow *nswindow)
{
    nsIScriptSecurityManager *secman;
    nsIPrincipal             *nspri;
    nsIGlobalObject          *nsglo;
    nsIXMLHttpRequest        *nsxhr;
    nsresult                  nsres;

    nsres = nsIServiceManager_GetServiceByContractID(pServMgr,
            NS_SCRIPTSECURITYMANAGER_CONTRACTID,
            &IID_nsIScriptSecurityManager, (void**)&secman);
    if(NS_FAILED(nsres)) {
        ERR("Could not get sec manager service: %08x\n", nsres);
        return NULL;
    }

    nsres = nsIScriptSecurityManager_GetSystemPrincipal(secman, &nspri);
    nsIScriptSecurityManager_Release(secman);
    if(NS_FAILED(nsres)) {
        ERR("GetSystemPrincipal failed: %08x\n", nsres);
        return NULL;
    }

    nsres = nsIDOMWindow_QueryInterface(nswindow, &IID_nsIGlobalObject, (void **)&nsglo);
    assert(nsres == NS_OK);

    nsres = nsIComponentManager_CreateInstanceByContractID(pCompMgr,
            NS_XMLHTTPREQUEST_CONTRACTID, NULL, &IID_nsIXMLHttpRequest,
            (void**)&nsxhr);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIXMLHttpRequest: %08x\n", nsres);
        nsISupports_Release(nspri);
        nsIGlobalObject_Release(nsglo);
        return NULL;
    }

    nsres = nsIXMLHttpRequest_Init(nsxhr, nspri, NULL, nsglo, NULL, NULL);

    nsISupports_Release(nspri);
    nsIGlobalObject_Release(nsglo);
    if(NS_FAILED(nsres)) {
        ERR("nsIXMLHttpRequest_Init failed: %08x\n", nsres);
        nsIXMLHttpRequest_Release(nsxhr);
        return NULL;
    }
    return nsxhr;
}