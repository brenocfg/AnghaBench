#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t ActionIndex; } ;
struct TYPE_9__ {TYPE_2__ AsyncExt; } ;
struct TYPE_11__ {TYPE_3__ FunctionParams; int /*<<< orphan*/  (* pInitCallback ) (int /*<<< orphan*/ ) ;TYPE_1__* ObjPool; } ;
struct TYPE_10__ {int /*<<< orphan*/  Status; } ;
struct TYPE_7__ {int /*<<< orphan*/  SyncObj; int /*<<< orphan*/  pRespArgs; } ;
typedef  TYPE_4__ InitComplete_t ;

/* Variables and functions */
 scalar_t__ _SL_RESP_ARGS_START (void*) ; 
 int /*<<< orphan*/  _SlDrvProtectionObjLockWaitForever () ; 
 int /*<<< orphan*/  _SlDrvProtectionObjUnLock () ; 
 int /*<<< orphan*/  _SlDrvReleasePoolObj (size_t) ; 
 int /*<<< orphan*/  _SlDrvSyncObjSignal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _sl_GetStartResponseConvert (int /*<<< orphan*/ ) ; 
 TYPE_6__* g_pCB ; 
 int /*<<< orphan*/  sl_Memcpy (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void _sl_HandleAsync_InitComplete(void *pVoidBuf)
{
    InitComplete_t     *pMsgArgs   = (InitComplete_t *)_SL_RESP_ARGS_START(pVoidBuf);

    _SlDrvProtectionObjLockWaitForever();

    if(g_pCB->pInitCallback)
    {
        g_pCB->pInitCallback(_sl_GetStartResponseConvert(pMsgArgs->Status));
    }
    else
    {
        sl_Memcpy(g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs, pMsgArgs, sizeof(InitComplete_t));
        _SlDrvSyncObjSignal(&g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].SyncObj);
    }
    
   _SlDrvProtectionObjUnLock();
   
    if(g_pCB->pInitCallback)
    {
        _SlDrvReleasePoolObj(g_pCB->FunctionParams.AsyncExt.ActionIndex);
    }

}