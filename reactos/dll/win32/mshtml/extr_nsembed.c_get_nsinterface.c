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
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsIInterfaceRequestor ;
typedef  int /*<<< orphan*/  REFIID ;

/* Variables and functions */
 int /*<<< orphan*/  IID_nsIInterfaceRequestor ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIInterfaceRequestor_GetInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  nsIInterfaceRequestor_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsISupports_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

nsresult get_nsinterface(nsISupports *iface, REFIID riid, void **ppv)
{
    nsIInterfaceRequestor *iface_req;
    nsresult nsres;

    nsres = nsISupports_QueryInterface(iface, &IID_nsIInterfaceRequestor, (void**)&iface_req);
    if(NS_FAILED(nsres))
        return nsres;

    nsres = nsIInterfaceRequestor_GetInterface(iface_req, riid, ppv);
    nsIInterfaceRequestor_Release(iface_req);

    return nsres;
}