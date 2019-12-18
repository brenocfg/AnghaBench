#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int _u8 ;
typedef  int /*<<< orphan*/  _SlPoolObj_t ;
typedef  int /*<<< orphan*/  _SlDriverCb_t ;
struct TYPE_7__ {int /*<<< orphan*/  TxSyncObj; int /*<<< orphan*/  TxLockObj; int /*<<< orphan*/  TxPoolCnt; } ;
struct TYPE_8__ {int NextIndex; int ActivePoolIdx; int PendingPoolIdx; TYPE_1__ FlowContCB; int /*<<< orphan*/  SyncObj; struct TYPE_8__* ObjPool; int /*<<< orphan*/  AdditionalData; scalar_t__ FreePoolIdx; int /*<<< orphan*/  ProtectionLockObj; int /*<<< orphan*/  GlobalLockObj; int /*<<< orphan*/  CmdSyncObj; } ;
struct TYPE_9__ {TYPE_2__ DriverCB; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_CONT_MIN ; 
 int /*<<< orphan*/  MALLOC_OK_CHECK (TYPE_2__*) ; 
 int MAX_CONCURRENT_ACTIONS ; 
 int /*<<< orphan*/  OSI_RET_OK_CHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ RxIrqCnt ; 
 int /*<<< orphan*/  SL_MAX_SOCKETS ; 
 int /*<<< orphan*/  _SlDrvMemZero (TYPE_2__*,int) ; 
 scalar_t__ gFirstCmdMode ; 
 TYPE_4__ g_StatMem ; 
 TYPE_2__* g_pCB ; 
 int /*<<< orphan*/  sl_LockObjCreate (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* sl_Malloc (int) ; 
 int /*<<< orphan*/  sl_SyncObjClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_SyncObjCreate (int /*<<< orphan*/ *,char*) ; 

void _SlDrvDriverCBInit(void)
{
    _u8          Idx =0;

#if (SL_MEMORY_MGMT == SL_MEMORY_MGMT_DYNAMIC)
    g_pCB = sl_Malloc(sizeof(_SlDriverCb_t));
#else
    g_pCB = &(g_StatMem.DriverCB);
#endif
    MALLOC_OK_CHECK(g_pCB);

    
    _SlDrvMemZero(g_pCB, sizeof(_SlDriverCb_t));
    RxIrqCnt = 0;
    OSI_RET_OK_CHECK( sl_SyncObjCreate(&g_pCB->CmdSyncObj, "CmdSyncObj") );
    sl_SyncObjClear(&g_pCB->CmdSyncObj);

    OSI_RET_OK_CHECK( sl_LockObjCreate(&g_pCB->GlobalLockObj, "GlobalLockObj") );
    OSI_RET_OK_CHECK( sl_LockObjCreate(&g_pCB->ProtectionLockObj, "ProtectionLockObj") );

    /* Init Drv object */
    _SlDrvMemZero(&g_pCB->ObjPool[0], MAX_CONCURRENT_ACTIONS*sizeof(_SlPoolObj_t));

    /* place all Obj in the free list*/
    g_pCB->FreePoolIdx = 0;

    for (Idx = 0 ; Idx < MAX_CONCURRENT_ACTIONS ; Idx++)
    {
        g_pCB->ObjPool[Idx].NextIndex = Idx + 1;
        g_pCB->ObjPool[Idx].AdditionalData = SL_MAX_SOCKETS;

        OSI_RET_OK_CHECK( sl_SyncObjCreate(&g_pCB->ObjPool[Idx].SyncObj, "SyncObj"));
        sl_SyncObjClear(&g_pCB->ObjPool[Idx].SyncObj);
    }

     g_pCB->ActivePoolIdx = MAX_CONCURRENT_ACTIONS;
     g_pCB->PendingPoolIdx = MAX_CONCURRENT_ACTIONS;

    /* Flow control init */
    g_pCB->FlowContCB.TxPoolCnt = FLOW_CONT_MIN;
    OSI_RET_OK_CHECK(sl_LockObjCreate(&g_pCB->FlowContCB.TxLockObj, "TxLockObj"));
    OSI_RET_OK_CHECK(sl_SyncObjCreate(&g_pCB->FlowContCB.TxSyncObj, "TxSyncObj"));
    
    gFirstCmdMode = 0;  

}