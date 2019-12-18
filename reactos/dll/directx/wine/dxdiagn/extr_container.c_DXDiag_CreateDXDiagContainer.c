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
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_4__ {TYPE_2__ IDxDiagContainer_iface; int /*<<< orphan*/ * pProv; int /*<<< orphan*/ * cont; scalar_t__ ref; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  IDxDiagProvider ;
typedef  int /*<<< orphan*/  IDxDiagContainerImpl_Container ;
typedef  TYPE_1__ IDxDiagContainerImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DxDiagContainer_Vtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDxDiagContainerImpl_QueryInterface (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDxDiagProvider_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

HRESULT DXDiag_CreateDXDiagContainer(REFIID riid, IDxDiagContainerImpl_Container *cont, IDxDiagProvider *pProv, LPVOID *ppobj) {
  IDxDiagContainerImpl* container;

  TRACE("(%s, %p)\n", debugstr_guid(riid), ppobj);

  container = HeapAlloc(GetProcessHeap(), 0, sizeof(IDxDiagContainerImpl));
  if (NULL == container) {
    *ppobj = NULL;
    return E_OUTOFMEMORY;
  }
  container->IDxDiagContainer_iface.lpVtbl = &DxDiagContainer_Vtbl;
  container->ref = 0; /* will be inited with QueryInterface */
  container->cont = cont;
  container->pProv = pProv;
  IDxDiagProvider_AddRef(pProv);
  return IDxDiagContainerImpl_QueryInterface(&container->IDxDiagContainer_iface, riid, ppobj);
}