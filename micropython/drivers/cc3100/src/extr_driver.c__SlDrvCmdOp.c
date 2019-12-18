#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int _u32 ;
typedef  scalar_t__ _SlReturnVal_t ;
typedef  int /*<<< orphan*/  _SlCmdExt_t ;
typedef  int /*<<< orphan*/  _SlCmdCtrl_t ;
struct TYPE_2__ {int /*<<< orphan*/  GlobalLockObj; int /*<<< orphan*/  IsCmdRespWaited; } ;

/* Variables and functions */
 int CPU_FREQ_IN_MHZ ; 
 int /*<<< orphan*/  DBG_MSG ; 
 int /*<<< orphan*/  MSG_312 ; 
 int /*<<< orphan*/  MSG_314 ; 
 scalar_t__ SL_OS_RET_CODE_OK ; 
 int /*<<< orphan*/  SL_TRACE0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int USEC_DELAY ; 
 scalar_t__ _SlDrvMsgReadCmdCtx () ; 
 scalar_t__ _SlDrvMsgWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  _SlDrvObjLockWaitForever (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SlDrvObjUnLock (int /*<<< orphan*/ *) ; 
 int gFirstCmdMode ; 
 TYPE_1__* g_pCB ; 

_SlReturnVal_t _SlDrvCmdOp(
    _SlCmdCtrl_t  *pCmdCtrl ,
    void          *pTxRxDescBuff ,
    _SlCmdExt_t   *pCmdExt)
{
    _SlReturnVal_t RetVal;

    
    _SlDrvObjLockWaitForever(&g_pCB->GlobalLockObj);
    
    g_pCB->IsCmdRespWaited = TRUE;

    SL_TRACE0(DBG_MSG, MSG_312, "_SlDrvCmdOp: call _SlDrvMsgWrite");


    /* send the message */
    RetVal = _SlDrvMsgWrite(pCmdCtrl, pCmdExt, pTxRxDescBuff);

    if(SL_OS_RET_CODE_OK == RetVal)
    {

#ifndef SL_IF_TYPE_UART    
        /* Waiting for SPI to stabilize after first command */
        if( 0 == gFirstCmdMode )
        {
            volatile _u32 CountVal = 0;
            gFirstCmdMode = 1;
            CountVal = CPU_FREQ_IN_MHZ*USEC_DELAY;
            while( CountVal-- );
        }   
#endif 
        /* wait for respond */
        RetVal = _SlDrvMsgReadCmdCtx(); /* will free global lock */
        SL_TRACE0(DBG_MSG, MSG_314, "_SlDrvCmdOp: exited _SlDrvMsgReadCmdCtx");
    }
    else
    {
        _SlDrvObjUnLock(&g_pCB->GlobalLockObj);
    }
    
    return RetVal;
}