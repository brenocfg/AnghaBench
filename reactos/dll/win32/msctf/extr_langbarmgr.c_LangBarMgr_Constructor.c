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
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int refCount; TYPE_1__ ITfLangBarMgr_iface; } ;
typedef  TYPE_2__ LangBarMgr ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LangBarMgr_LangBarMgrVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

HRESULT LangBarMgr_Constructor(IUnknown *pUnkOuter, IUnknown **ppOut)
{
    LangBarMgr *This;
    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    This = HeapAlloc(GetProcessHeap(),0,sizeof(LangBarMgr));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->ITfLangBarMgr_iface.lpVtbl = &LangBarMgr_LangBarMgrVtbl;
    This->refCount = 1;

    *ppOut = (IUnknown *)&This->ITfLangBarMgr_iface;
    TRACE("returning %p\n", *ppOut);
    return S_OK;
}