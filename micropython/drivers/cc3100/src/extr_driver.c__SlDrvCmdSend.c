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
typedef  int /*<<< orphan*/  _u8 ;
typedef  int /*<<< orphan*/  _SlReturnVal_t ;
typedef  int /*<<< orphan*/  _SlFunctionParams_t ;
typedef  int /*<<< orphan*/  _SlCmdExt_t ;
typedef  int /*<<< orphan*/  _SlCmdCtrl_t ;
struct TYPE_2__ {int /*<<< orphan*/  FunctionParams; int /*<<< orphan*/  IsCmdRespWaited; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_312 ; 
 int /*<<< orphan*/  SL_TRACE0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _SlDrvMsgWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 TYPE_1__* g_pCB ; 
 int /*<<< orphan*/  sl_Memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

_SlReturnVal_t _SlDrvCmdSend(
    _SlCmdCtrl_t  *pCmdCtrl ,
    void          *pTxRxDescBuff ,
    _SlCmdExt_t   *pCmdExt)
{
    _SlReturnVal_t RetVal;
    _u8            IsCmdRespWaitedOriginalVal;

    _SlFunctionParams_t originalFuncParms;

    /* save the current RespWait flag before clearing it */
    IsCmdRespWaitedOriginalVal = g_pCB->IsCmdRespWaited;

    /* save the current command parameters */
    sl_Memcpy(&originalFuncParms,  &g_pCB->FunctionParams, sizeof(_SlFunctionParams_t));

    g_pCB->IsCmdRespWaited = FALSE;
  
    SL_TRACE0(DBG_MSG, MSG_312, "_SlDrvCmdSend: call _SlDrvMsgWrite");

    /* send the message */
    RetVal = _SlDrvMsgWrite(pCmdCtrl, pCmdExt, pTxRxDescBuff);

    /* restore the original RespWait flag */
    g_pCB->IsCmdRespWaited = IsCmdRespWaitedOriginalVal;

    /* restore the original command parameters  */
    sl_Memcpy(&g_pCB->FunctionParams, &originalFuncParms, sizeof(_SlFunctionParams_t));

    return RetVal;


}