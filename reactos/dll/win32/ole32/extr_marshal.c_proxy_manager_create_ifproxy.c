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
struct proxy_manager {int /*<<< orphan*/  cs; int /*<<< orphan*/  interfaces; int /*<<< orphan*/  IMultiQI_iface; } ;
struct TYPE_3__ {int /*<<< orphan*/  cPublicRefs; int /*<<< orphan*/  ipid; } ;
struct ifproxy {int /*<<< orphan*/  entry; int /*<<< orphan*/ * chan; int /*<<< orphan*/ * proxy; int /*<<< orphan*/ * iface; scalar_t__ refs; int /*<<< orphan*/  iid; TYPE_1__ stdobjref; struct proxy_manager* parent; } ;
typedef  TYPE_1__ STDOBJREF ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IRpcChannelBuffer ;
typedef  int /*<<< orphan*/  IPSFactoryBuffer ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct ifproxy* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IMultiQI_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IPSFactoryBuffer_CreateProxy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPSFactoryBuffer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IRpcProxyBuffer_Connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,struct ifproxy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 scalar_t__ get_facbuf_for_iid (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ifproxy_destroy (struct ifproxy*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT proxy_manager_create_ifproxy(
    struct proxy_manager * This, const STDOBJREF *stdobjref, REFIID riid,
    IRpcChannelBuffer * channel, struct ifproxy ** iif_out)
{
    HRESULT hr;
    IPSFactoryBuffer * psfb;
    struct ifproxy * ifproxy = HeapAlloc(GetProcessHeap(), 0, sizeof(*ifproxy));
    if (!ifproxy) return E_OUTOFMEMORY;

    list_init(&ifproxy->entry);

    ifproxy->parent = This;
    ifproxy->stdobjref = *stdobjref;
    ifproxy->iid = *riid;
    ifproxy->refs = 0;
    ifproxy->proxy = NULL;

    assert(channel);
    ifproxy->chan = channel; /* FIXME: we should take the binding strings and construct the channel in this function */

    /* the IUnknown interface is special because it does not have a
     * proxy associated with the ifproxy as we handle IUnknown ourselves */
    if (IsEqualIID(riid, &IID_IUnknown))
    {
        ifproxy->iface = &This->IMultiQI_iface;
        IMultiQI_AddRef(&This->IMultiQI_iface);
        hr = S_OK;
    }
    else
    {
        hr = get_facbuf_for_iid(riid, &psfb);
        if (hr == S_OK)
        {
            /* important note: the outer unknown is set to the proxy manager.
             * This ensures the COM identity rules are not violated, by having a
             * one-to-one mapping of objects on the proxy side to objects on the
             * stub side, no matter which interface you view the object through */
            hr = IPSFactoryBuffer_CreateProxy(psfb, (IUnknown*)&This->IMultiQI_iface, riid,
                                              &ifproxy->proxy, &ifproxy->iface);
            IPSFactoryBuffer_Release(psfb);
            if (hr != S_OK)
                ERR("Could not create proxy for interface %s, error 0x%08x\n",
                    debugstr_guid(riid), hr);
        }
        else
            ERR("Could not get IPSFactoryBuffer for interface %s, error 0x%08x\n",
                debugstr_guid(riid), hr);

        if (hr == S_OK)
            hr = IRpcProxyBuffer_Connect(ifproxy->proxy, ifproxy->chan);
    }

    if (hr == S_OK)
    {
        EnterCriticalSection(&This->cs);
        list_add_tail(&This->interfaces, &ifproxy->entry);
        LeaveCriticalSection(&This->cs);

        *iif_out = ifproxy;
        TRACE("ifproxy %p created for IPID %s, interface %s with %u public refs\n",
              ifproxy, debugstr_guid(&stdobjref->ipid), debugstr_guid(riid), stdobjref->cPublicRefs);
    }
    else
        ifproxy_destroy(ifproxy);

    return hr;
}