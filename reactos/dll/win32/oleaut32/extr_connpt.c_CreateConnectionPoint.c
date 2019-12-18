#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; int maxSinks; TYPE_1__ IConnectionPoint_iface; scalar_t__ nSinks; void* sinks; int /*<<< orphan*/  iid; int /*<<< orphan*/ * Obj; } ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IConnectionPoint ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ ConnectionPointImpl ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointImpl_VTable ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MAXSINKS ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 

HRESULT CreateConnectionPoint(IUnknown *pUnk, REFIID riid,
			      IConnectionPoint **pCP)
{
  ConnectionPointImpl *Obj;

  TRACE("(%p %s %p)\n", pUnk, debugstr_guid(riid), pCP);

  *pCP = NULL;
  Obj = HeapAlloc(GetProcessHeap(), 0, sizeof(*Obj));
  if (!Obj)
    return E_OUTOFMEMORY;

  Obj->IConnectionPoint_iface.lpVtbl = &ConnectionPointImpl_VTable;
  Obj->Obj = pUnk;
  Obj->ref = 1;
  Obj->iid = *riid;
  Obj->maxSinks = MAXSINKS;
  Obj->sinks = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IUnknown*) * MAXSINKS);
  Obj->nSinks = 0;

  *pCP = &Obj->IConnectionPoint_iface;
  return S_OK;
}