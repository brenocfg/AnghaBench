#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_14__ {int /*<<< orphan*/  piid; } ;
struct TYPE_18__ {TYPE_3__ header; scalar_t__ Vtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int TableVersion; scalar_t__* pDelegatedIIDs; TYPE_2__** pStubVtblList; TYPE_7__** pProxyVtblList; int /*<<< orphan*/ * pNamesArray; } ;
struct TYPE_15__ {int RefCount; int /*<<< orphan*/ * base_object; int /*<<< orphan*/ * base_proxy; scalar_t__ PVtbl; TYPE_6__ IRpcProxyBuffer_iface; int /*<<< orphan*/ * pChannel; int /*<<< orphan*/  pPSFactory; int /*<<< orphan*/  name; int /*<<< orphan*/ * pUnkOuter; int /*<<< orphan*/  piid; } ;
struct TYPE_12__ {int /*<<< orphan*/  DispatchTableCount; } ;
struct TYPE_13__ {TYPE_1__ header; } ;
typedef  TYPE_4__ StdProxyImpl ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_5__ ProxyFileInfo ;
typedef  int /*<<< orphan*/  PCInterfaceName ;
typedef  scalar_t__* LPVOID ;
typedef  int /*<<< orphan*/ * LPUNKNOWN ;
typedef  TYPE_6__* LPRPCPROXYBUFFER ;
typedef  int /*<<< orphan*/  LPPSFACTORYBUFFER ;
typedef  int /*<<< orphan*/  IUnknownVtbl ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_7__ CInterfaceProxyVtbl ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  IPSFactoryBuffer_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_E_UNEXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StdProxy_Vtbl ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  create_proxy (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_stubless_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT StdProxy_Construct(REFIID riid,
                           LPUNKNOWN pUnkOuter,
                           const ProxyFileInfo *ProxyInfo,
                           int Index,
                           LPPSFACTORYBUFFER pPSFactory,
                           LPRPCPROXYBUFFER *ppProxy,
                           LPVOID *ppvObj)
{
  StdProxyImpl *This;
  PCInterfaceName name = ProxyInfo->pNamesArray[Index];
  CInterfaceProxyVtbl *vtbl = ProxyInfo->pProxyVtblList[Index];

  TRACE("(%p,%p,%p,%p,%p) %s\n", pUnkOuter, vtbl, pPSFactory, ppProxy, ppvObj, name);

  /* TableVersion = 2 means it is the stubless version of CInterfaceProxyVtbl */
  if (ProxyInfo->TableVersion > 1) {
    ULONG count = ProxyInfo->pStubVtblList[Index]->header.DispatchTableCount;
    vtbl = (CInterfaceProxyVtbl *)((const void **)vtbl + 1);
    TRACE("stubless vtbl %p: count=%d\n", vtbl->Vtbl, count );
    fill_stubless_table( (IUnknownVtbl *)vtbl->Vtbl, count );
  }

  if (!IsEqualGUID(vtbl->header.piid, riid)) {
    ERR("IID mismatch during proxy creation\n");
    return RPC_E_UNEXPECTED;
  }

  This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(StdProxyImpl));
  if (!This) return E_OUTOFMEMORY;

  if (!pUnkOuter) pUnkOuter = (IUnknown *)This;
  This->IRpcProxyBuffer_iface.lpVtbl = &StdProxy_Vtbl;
  This->PVtbl = vtbl->Vtbl;
  /* one reference for the proxy */
  This->RefCount = 1;
  This->piid = vtbl->header.piid;
  This->base_object = NULL;
  This->base_proxy = NULL;
  This->pUnkOuter = pUnkOuter;
  This->name = name;
  This->pPSFactory = pPSFactory;
  This->pChannel = NULL;

  if(ProxyInfo->pDelegatedIIDs && ProxyInfo->pDelegatedIIDs[Index])
  {
      HRESULT r = create_proxy( ProxyInfo->pDelegatedIIDs[Index], NULL,
                                &This->base_proxy, (void **)&This->base_object );
      if (FAILED(r))
      {
          HeapFree( GetProcessHeap(), 0, This );
          return r;
      }
  }

  *ppProxy = &This->IRpcProxyBuffer_iface;
  *ppvObj = &This->PVtbl;
  IUnknown_AddRef((IUnknown *)*ppvObj);
  IPSFactoryBuffer_AddRef(pPSFactory);

  TRACE( "iid=%s this %p proxy %p obj %p vtbl %p base proxy %p base obj %p\n",
         debugstr_guid(riid), This, *ppProxy, *ppvObj, This->PVtbl, This->base_proxy, This->base_object );
  return S_OK;
}