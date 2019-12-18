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
typedef  size_t _u8 ;
struct TYPE_4__ {TYPE_1__* ObjPool; } ;
struct TYPE_3__ {size_t* pRespArgs; } ;

/* Variables and functions */
 size_t MAX_CONCURRENT_ACTIONS ; 
 int /*<<< orphan*/  _SlDrvProtectionObjLockWaitForever () ; 
 int /*<<< orphan*/  _SlDrvProtectionObjUnLock () ; 
 size_t _SlDrvWaitForPoolObj (size_t,size_t) ; 
 TYPE_2__* g_pCB ; 

_u8 _SlDrvProtectAsyncRespSetting(_u8 *pAsyncRsp, _u8 ActionID, _u8 SocketID)
{
    _u8 ObjIdx;


    /* Use Obj to issue the command, if not available try later */
    ObjIdx = _SlDrvWaitForPoolObj(ActionID, SocketID);

    if (MAX_CONCURRENT_ACTIONS != ObjIdx)
    {
        _SlDrvProtectionObjLockWaitForever();
        g_pCB->ObjPool[ObjIdx].pRespArgs = pAsyncRsp;
        _SlDrvProtectionObjUnLock();
    }

    return ObjIdx;
}