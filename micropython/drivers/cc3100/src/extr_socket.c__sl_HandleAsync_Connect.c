#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int sd; int /*<<< orphan*/  statusOrLen; } ;
typedef  TYPE_4__ _SocketResponse_t ;
struct TYPE_7__ {size_t ActionIndex; } ;
struct TYPE_8__ {TYPE_2__ AsyncExt; } ;
struct TYPE_10__ {TYPE_3__ FunctionParams; TYPE_1__* ObjPool; } ;
struct TYPE_6__ {int /*<<< orphan*/  SyncObj; int /*<<< orphan*/ * pRespArgs; } ;

/* Variables and functions */
 int BSD_SOCKET_ID_MASK ; 
 int SL_MAX_SOCKETS ; 
 int /*<<< orphan*/  VERIFY_PROTOCOL (int) ; 
 int /*<<< orphan*/  VERIFY_SOCKET_CB (int) ; 
 scalar_t__ _SL_RESP_ARGS_START (void*) ; 
 int /*<<< orphan*/  _SlDrvProtectionObjLockWaitForever () ; 
 int /*<<< orphan*/  _SlDrvProtectionObjUnLock () ; 
 int /*<<< orphan*/  _SlDrvSyncObjSignal (int /*<<< orphan*/ *) ; 
 TYPE_5__* g_pCB ; 

void _sl_HandleAsync_Connect(void *pVoidBuf)
{
    _SocketResponse_t          *pMsgArgs   = (_SocketResponse_t *)_SL_RESP_ARGS_START(pVoidBuf);

    _SlDrvProtectionObjLockWaitForever();

    VERIFY_PROTOCOL((pMsgArgs->sd & BSD_SOCKET_ID_MASK) <= SL_MAX_SOCKETS);
    VERIFY_SOCKET_CB(NULL != g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs);
    

    ((_SocketResponse_t *)(g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs))->sd = pMsgArgs->sd;
    ((_SocketResponse_t *)(g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].pRespArgs))->statusOrLen = pMsgArgs->statusOrLen;


    _SlDrvSyncObjSignal(&g_pCB->ObjPool[g_pCB->FunctionParams.AsyncExt.ActionIndex].SyncObj);
    _SlDrvProtectionObjUnLock();
    return;
}