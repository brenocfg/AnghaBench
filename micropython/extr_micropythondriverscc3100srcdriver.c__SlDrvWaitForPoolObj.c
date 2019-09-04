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
struct TYPE_4__ {scalar_t__ FreePoolIdx; int ActiveActionsBitmap; size_t PendingPoolIdx; size_t ActivePoolIdx; TYPE_1__* ObjPool; } ;
struct TYPE_3__ {scalar_t__ NextIndex; size_t ActionID; size_t AdditionalData; int /*<<< orphan*/  SyncObj; } ;

/* Variables and functions */
 scalar_t__ MAX_CONCURRENT_ACTIONS ; 
 size_t SL_MAX_SOCKETS ; 
 int /*<<< orphan*/  _SlDrvProtectionObjLockWaitForever () ; 
 int /*<<< orphan*/  _SlDrvProtectionObjUnLock () ; 
 int /*<<< orphan*/  _SlDrvSyncObjWaitForever (int /*<<< orphan*/ *) ; 
 TYPE_2__* g_pCB ; 

_u8 _SlDrvWaitForPoolObj(_u8 ActionID, _u8 SocketID)
{
    _u8 CurrObjIndex = MAX_CONCURRENT_ACTIONS;

    /* Get free object  */
            _SlDrvProtectionObjLockWaitForever();
    if (MAX_CONCURRENT_ACTIONS > g_pCB->FreePoolIdx)
    {
        /* save the current obj index */
        CurrObjIndex = g_pCB->FreePoolIdx;
        /* set the new free index */
#ifndef SL_TINY_EXT
        if (MAX_CONCURRENT_ACTIONS > g_pCB->ObjPool[CurrObjIndex].NextIndex)
        {
            g_pCB->FreePoolIdx = g_pCB->ObjPool[CurrObjIndex].NextIndex;
        }
        else
#endif           
        {
            /* No further free actions available */
            g_pCB->FreePoolIdx = MAX_CONCURRENT_ACTIONS;
        }
    }
    else
    {
		_SlDrvProtectionObjUnLock();
        return CurrObjIndex;
    }
    g_pCB->ObjPool[CurrObjIndex].ActionID = (_u8)ActionID;
    if (SL_MAX_SOCKETS > SocketID)
    {
        g_pCB->ObjPool[CurrObjIndex].AdditionalData = SocketID;
    }
#ifndef SL_TINY_EXT
    /*In case this action is socket related, SocketID bit will be on
    In case SocketID is set to SL_MAX_SOCKETS, the socket is not relevant to the action. In that case ActionID bit will be on */
	while ( ( (SL_MAX_SOCKETS > SocketID) && (g_pCB->ActiveActionsBitmap & (1<<SocketID)) ) || 
            ( (g_pCB->ActiveActionsBitmap & (1<<ActionID)) && (SL_MAX_SOCKETS == SocketID) ) )
    {
        /* action in progress - move to pending list */
        g_pCB->ObjPool[CurrObjIndex].NextIndex = g_pCB->PendingPoolIdx;
        g_pCB->PendingPoolIdx = CurrObjIndex;
		_SlDrvProtectionObjUnLock();
        
        /* wait for action to be free */
        _SlDrvSyncObjWaitForever(&g_pCB->ObjPool[CurrObjIndex].SyncObj);
        
        /* set params and move to active (remove from pending list at _SlDrvReleasePoolObj) */
        _SlDrvProtectionObjLockWaitForever();
    }
#endif
    /* mark as active. Set socket as active if action is on socket, otherwise mark action as active */
    if (SL_MAX_SOCKETS > SocketID)
    {
        g_pCB->ActiveActionsBitmap |= (1<<SocketID);
    }
    else
    {
        g_pCB->ActiveActionsBitmap |= (1<<ActionID);
    }
    /* move to active list  */
    g_pCB->ObjPool[CurrObjIndex].NextIndex = g_pCB->ActivePoolIdx;
    g_pCB->ActivePoolIdx = CurrObjIndex;	
    /* unlock */
	_SlDrvProtectionObjUnLock();
    return CurrObjIndex;
}