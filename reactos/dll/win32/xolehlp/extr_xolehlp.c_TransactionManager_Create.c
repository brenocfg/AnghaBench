#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; TYPE_5__ ITransactionDispenser_iface; TYPE_3__ ITransactionImport_iface; TYPE_2__ ITransactionImportWhereabouts_iface; TYPE_1__ IResourceManagerFactory2_iface; } ;
typedef  TYPE_4__ TransactionManager ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ITransactionDispenser_QueryInterface (TYPE_5__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  ITransactionDispenser_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  ResourceManagerFactory2_Vtbl ; 
 int /*<<< orphan*/  TransactionDispenser_Vtbl ; 
 int /*<<< orphan*/  TransactionImportWhereabouts_Vtbl ; 
 int /*<<< orphan*/  TransactionImport_Vtbl ; 

__attribute__((used)) static HRESULT TransactionManager_Create(REFIID riid, void **ppv)
{
    TransactionManager *This;
    HRESULT ret;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(TransactionManager));
    if (!This) return E_OUTOFMEMORY;

    This->ITransactionDispenser_iface.lpVtbl = &TransactionDispenser_Vtbl;
    This->IResourceManagerFactory2_iface.lpVtbl = &ResourceManagerFactory2_Vtbl;
    This->ITransactionImportWhereabouts_iface.lpVtbl = &TransactionImportWhereabouts_Vtbl;
    This->ITransactionImport_iface.lpVtbl = &TransactionImport_Vtbl;
    This->ref = 1;

    ret = ITransactionDispenser_QueryInterface(&This->ITransactionDispenser_iface, riid, ppv);
    ITransactionDispenser_Release(&This->ITransactionDispenser_iface);

    return ret;
}