#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int _SlSd_t ;
typedef  int /*<<< orphan*/  _SlReturnVal_t ;
typedef  int /*<<< orphan*/  _SlCmdExt_t ;
typedef  int /*<<< orphan*/  _SlCmdCtrl_t ;
struct TYPE_3__ {scalar_t__ TxPoolCnt; int /*<<< orphan*/  TxLockObj; int /*<<< orphan*/  TxSyncObj; } ;
struct TYPE_4__ {int SocketTXFailure; int SocketNonBlocking; int /*<<< orphan*/  GlobalLockObj; TYPE_1__ FlowContCB; } ;

/* Variables and functions */
 int BSD_SOCKET_ID_MASK ; 
 scalar_t__ FLOW_CONT_MIN ; 
 int /*<<< orphan*/  SL_EAGAIN ; 
 int /*<<< orphan*/  SL_SOC_ERROR ; 
 int /*<<< orphan*/  VERIFY_PROTOCOL (int) ; 
 int /*<<< orphan*/  _SlDrvMsgWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  _SlDrvObjLockWaitForever (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SlDrvObjUnLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SlDrvSyncObjWaitForever (int /*<<< orphan*/ *) ; 
 TYPE_2__* g_pCB ; 
 int /*<<< orphan*/  sl_SyncObjClear (int /*<<< orphan*/ *) ; 

_SlReturnVal_t _SlDrvDataWriteOp(
    _SlSd_t             Sd,
    _SlCmdCtrl_t  *pCmdCtrl ,
    void                *pTxRxDescBuff ,
    _SlCmdExt_t         *pCmdExt)
{
    _SlReturnVal_t  RetVal = SL_EAGAIN; /*  initiated as SL_EAGAIN for the non blocking mode */
    while( 1 )
    {
        /*  Do Flow Control check/update for DataWrite operation */
    _SlDrvObjLockWaitForever(&g_pCB->FlowContCB.TxLockObj);

        /*  Clear SyncObj for the case it was signalled before TxPoolCnt */
        /*  dropped below '1' (last Data buffer was taken) */
        /* OSI_RET_OK_CHECK( sl_SyncObjClear(&g_pCB->FlowContCB.TxSyncObj) ); */
        sl_SyncObjClear(&g_pCB->FlowContCB.TxSyncObj);

        /*  we have indication that the last send has failed - socket is no longer valid for operations  */
        if(g_pCB->SocketTXFailure & (1<<(Sd & BSD_SOCKET_ID_MASK)))
        {
		_SlDrvObjUnLock(&g_pCB->FlowContCB.TxLockObj);
            return SL_SOC_ERROR;
        }
        if(g_pCB->FlowContCB.TxPoolCnt <= FLOW_CONT_MIN + 1)
        {
            /*  we have indication that this socket is set as blocking and we try to  */
            /*  unblock it - return an error */
            if( g_pCB->SocketNonBlocking & (1<< (Sd & BSD_SOCKET_ID_MASK)))
            {
            _SlDrvObjUnLock(&g_pCB->FlowContCB.TxLockObj);
                return RetVal;
            }
            /*  If TxPoolCnt was increased by other thread at this moment, */
            /*  TxSyncObj won't wait here */
        _SlDrvSyncObjWaitForever(&g_pCB->FlowContCB.TxSyncObj);
        }
        if(g_pCB->FlowContCB.TxPoolCnt > FLOW_CONT_MIN + 1 )
        {
            break;
        }
        else
        {
			_SlDrvObjUnLock(&g_pCB->FlowContCB.TxLockObj);
        }
    }

    _SlDrvObjLockWaitForever(&g_pCB->GlobalLockObj);
    

    VERIFY_PROTOCOL(g_pCB->FlowContCB.TxPoolCnt > FLOW_CONT_MIN + 1 );
    g_pCB->FlowContCB.TxPoolCnt--;

    _SlDrvObjUnLock(&g_pCB->FlowContCB.TxLockObj);
    
    /* send the message */
    RetVal =  _SlDrvMsgWrite(pCmdCtrl, pCmdExt, pTxRxDescBuff);

    _SlDrvObjUnLock(&g_pCB->GlobalLockObj);

    return RetVal;
}