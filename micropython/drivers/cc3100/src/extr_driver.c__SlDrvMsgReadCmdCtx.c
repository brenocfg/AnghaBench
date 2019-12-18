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
typedef  int /*<<< orphan*/  _SlSpawnEntryFunc_t ;
typedef  int /*<<< orphan*/  _SlReturnVal_t ;
struct TYPE_5__ {scalar_t__ RxMsgClass; int /*<<< orphan*/ * pAsyncBuf; } ;
struct TYPE_6__ {TYPE_1__ AsyncExt; } ;
struct TYPE_7__ {scalar_t__ IsCmdRespWaited; int /*<<< orphan*/  GlobalLockObj; int /*<<< orphan*/  CmdSyncObj; TYPE_2__ FunctionParams; int /*<<< orphan*/  RxDoneCnt; } ;

/* Variables and functions */
 scalar_t__ ASYNC_EVT_CLASS ; 
 scalar_t__ CMD_RESP_CLASS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SL_OS_RET_CODE_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VERIFY_RET_OK (int /*<<< orphan*/ ) ; 
 scalar_t__ _SL_PENDING_RX_MSG (TYPE_3__*) ; 
 int /*<<< orphan*/  _SlAsyncEventGenericHandler () ; 
 int /*<<< orphan*/  _SlDrvMsgRead () ; 
 scalar_t__ _SlDrvMsgReadSpawnCtx ; 
 int /*<<< orphan*/  _SlDrvObjUnLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SlDrvSyncObjWaitForever (int /*<<< orphan*/ *) ; 
 TYPE_3__* g_pCB ; 
 int /*<<< orphan*/  sl_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sl_Spawn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_SyncObjClear (int /*<<< orphan*/ *) ; 

_SlReturnVal_t _SlDrvMsgReadCmdCtx(void)
{

    /*  after command response is received and isCmdRespWaited */
    /*  flag is set FALSE, it is necessary to read out all */
    /*  Async messages in Commands context, because ssiDma_IsrHandleSignalFromSlave */
    /*  could have dispatched some Async messages to g_NwpIf.CmdSyncObj */
    /*  after command response but before this response has been processed */
    /*  by spi_singleRead and isCmdRespWaited was set FALSE. */
    while (TRUE == g_pCB->IsCmdRespWaited)
    {
        if(_SL_PENDING_RX_MSG(g_pCB))
        {
            VERIFY_RET_OK(_SlDrvMsgRead());
            g_pCB->RxDoneCnt++;

            if (CMD_RESP_CLASS == g_pCB->FunctionParams.AsyncExt.RxMsgClass)
            {
                g_pCB->IsCmdRespWaited = FALSE;

                /*  In case CmdResp has been read without  waiting on CmdSyncObj -  that */
                /*  Sync object. That to prevent old signal to be processed. */
                sl_SyncObjClear(&g_pCB->CmdSyncObj);
            }
            else if (ASYNC_EVT_CLASS == g_pCB->FunctionParams.AsyncExt.RxMsgClass)
            {
                /*  If Async event has been read in CmdResp context, check whether */
                /*  there is a handler for this event. If there is, spawn specific */
                /*  handler. Otherwise free the event's buffer. */
                /*  This way there will be no "dry shots" from CmdResp context to */
                /*  temporary context, i.e less waste of CPU and faster buffer */
                /*  release. */
                _SlAsyncEventGenericHandler();
                
                
#if (SL_MEMORY_MGMT == SL_MEMORY_MGMT_DYNAMIC)
                sl_Free(g_pCB->FunctionParams.AsyncExt.pAsyncBuf);
#else
                g_pCB->FunctionParams.AsyncExt.pAsyncBuf = NULL;
#endif
            }
        }
        else
        {
            /* CmdSyncObj will be signaled by IRQ */
             _SlDrvSyncObjWaitForever(&g_pCB->CmdSyncObj);
        }
    }

    /*  If there are more pending Rx Msgs after CmdResp is received, */
    /*  that means that these are Async, Dummy or Read Data Msgs. */
    /*  Spawn _SlDrvMsgReadSpawnCtx to trigger reading these messages from */
    /*  Temporary context. */
    /* sl_Spawn is activated, using a different context */

    _SlDrvObjUnLock(&g_pCB->GlobalLockObj);
    
    if(_SL_PENDING_RX_MSG(g_pCB))
    {
        sl_Spawn((_SlSpawnEntryFunc_t)_SlDrvMsgReadSpawnCtx, NULL, 0);
    }

    return SL_OS_RET_CODE_OK;
}