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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIContentSerializer ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_nsIContentSerializer ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_HTMLSERIALIZER_CONTRACTID ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIComponentManager_CreateInstanceByContractID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIContentSerializer_Flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIContentSerializer_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIContentSerializer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsnode_to_nsstring_rec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pCompMgr ; 

HRESULT nsnode_to_nsstring(nsIDOMNode *nsnode, nsAString *str)
{
    nsIContentSerializer *serializer;
    nsresult nsres;
    HRESULT hres;

    nsres = nsIComponentManager_CreateInstanceByContractID(pCompMgr,
            NS_HTMLSERIALIZER_CONTRACTID, NULL, &IID_nsIContentSerializer,
            (void**)&serializer);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIContentSerializer: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIContentSerializer_Init(serializer, 0, 100, NULL, FALSE, FALSE /* FIXME */);
    if(NS_FAILED(nsres))
        ERR("Init failed: %08x\n", nsres);

    hres = nsnode_to_nsstring_rec(serializer, nsnode, str);
    if(SUCCEEDED(hres)) {
        nsres = nsIContentSerializer_Flush(serializer, str);
        if(NS_FAILED(nsres))
            ERR("Flush failed: %08x\n", nsres);
    }

    nsIContentSerializer_Release(serializer);
    return hres;
}