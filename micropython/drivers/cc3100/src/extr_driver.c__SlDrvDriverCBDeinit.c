#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t _u8 ;
struct TYPE_5__ {int /*<<< orphan*/  TxSyncObj; int /*<<< orphan*/  TxLockObj; scalar_t__ TxPoolCnt; } ;
struct TYPE_7__ {size_t PendingPoolIdx; size_t ActivePoolIdx; scalar_t__ FreePoolIdx; TYPE_2__* ObjPool; int /*<<< orphan*/  ProtectionLockObj; int /*<<< orphan*/  GlobalLockObj; int /*<<< orphan*/  CmdSyncObj; TYPE_1__ FlowContCB; } ;
struct TYPE_6__ {int /*<<< orphan*/  SyncObj; } ;

/* Variables and functions */
 size_t MAX_CONCURRENT_ACTIONS ; 
 int /*<<< orphan*/  OSI_RET_OK_CHECK (int /*<<< orphan*/ ) ; 
 TYPE_3__* g_pCB ; 
 int /*<<< orphan*/  sl_Free (TYPE_3__*) ; 
 int /*<<< orphan*/  sl_LockObjDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_SyncObjDelete (int /*<<< orphan*/ *) ; 

void _SlDrvDriverCBDeinit()
{
    _u8  Idx =0;

    /* Flow control de-init */
    g_pCB->FlowContCB.TxPoolCnt = 0;
    OSI_RET_OK_CHECK(sl_LockObjDelete(&g_pCB->FlowContCB.TxLockObj));
    OSI_RET_OK_CHECK(sl_SyncObjDelete(&g_pCB->FlowContCB.TxSyncObj));
    
    OSI_RET_OK_CHECK( sl_SyncObjDelete(&g_pCB->CmdSyncObj) );
    OSI_RET_OK_CHECK( sl_LockObjDelete(&g_pCB->GlobalLockObj) );
    OSI_RET_OK_CHECK( sl_LockObjDelete(&g_pCB->ProtectionLockObj) );
        
 #ifndef SL_TINY_EXT
    for (Idx = 0; Idx < MAX_CONCURRENT_ACTIONS; Idx++)
 #endif
    {
	OSI_RET_OK_CHECK( sl_SyncObjDelete(&g_pCB->ObjPool[Idx].SyncObj) );   
    }

    g_pCB->FreePoolIdx = 0;
    g_pCB->PendingPoolIdx = MAX_CONCURRENT_ACTIONS;
    g_pCB->ActivePoolIdx = MAX_CONCURRENT_ACTIONS;

#if (SL_MEMORY_MGMT == SL_MEMORY_MGMT_DYNAMIC)
    sl_Free(g_pCB);
#else
    g_pCB = NULL;
#endif


    g_pCB = NULL;
}