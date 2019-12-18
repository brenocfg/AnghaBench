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
struct TYPE_4__ {size_t PendingPoolIdx; int ActiveActionsBitmap; size_t ActivePoolIdx; size_t FreePoolIdx; TYPE_1__* ObjPool; } ;
struct TYPE_3__ {scalar_t__ ActionID; int AdditionalData; size_t NextIndex; int /*<<< orphan*/ * pRespArgs; int /*<<< orphan*/  SyncObj; } ;

/* Variables and functions */
 int BSD_SOCKET_ID_MASK ; 
 size_t MAX_CONCURRENT_ACTIONS ; 
 int SL_MAX_SOCKETS ; 
 int /*<<< orphan*/  _SlDrvProtectionObjLockWaitForever () ; 
 int /*<<< orphan*/  _SlDrvProtectionObjUnLock () ; 
 int /*<<< orphan*/  _SlDrvSyncObjSignal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SlRemoveFromList (size_t*,size_t) ; 
 TYPE_2__* g_pCB ; 

void _SlDrvReleasePoolObj(_u8 ObjIdx)
{
#ifndef SL_TINY_EXT        
    _u8 PendingIndex;
#endif

     _SlDrvProtectionObjLockWaitForever();

      /* In Tiny mode, there is only one object pool so no pending actions are available */
#ifndef SL_TINY_EXT
    /* go over the pending list and release other pending action if needed */
	PendingIndex = g_pCB->PendingPoolIdx;
        
	while(MAX_CONCURRENT_ACTIONS > PendingIndex)
	{
		/* In case this action is socket related, SocketID is in use, otherwise will be set to SL_MAX_SOCKETS */
		if ( (g_pCB->ObjPool[PendingIndex].ActionID == g_pCB->ObjPool[ObjIdx].ActionID) && 
			( (SL_MAX_SOCKETS == (g_pCB->ObjPool[PendingIndex].AdditionalData & BSD_SOCKET_ID_MASK)) || 
			((SL_MAX_SOCKETS > (g_pCB->ObjPool[ObjIdx].AdditionalData & BSD_SOCKET_ID_MASK)) && ( (g_pCB->ObjPool[PendingIndex].AdditionalData & BSD_SOCKET_ID_MASK) == (g_pCB->ObjPool[ObjIdx].AdditionalData & BSD_SOCKET_ID_MASK) ))) )
		{
			/* remove from pending list */
			_SlRemoveFromList(&g_pCB->PendingPoolIdx, PendingIndex);
			 _SlDrvSyncObjSignal(&g_pCB->ObjPool[PendingIndex].SyncObj);
			 break;
		}
		PendingIndex = g_pCB->ObjPool[PendingIndex].NextIndex;
	}
#endif

		if (SL_MAX_SOCKETS > (g_pCB->ObjPool[ObjIdx].AdditionalData & BSD_SOCKET_ID_MASK))
		{
		/* unset socketID  */
			g_pCB->ActiveActionsBitmap &= ~(1<<(g_pCB->ObjPool[ObjIdx].AdditionalData & BSD_SOCKET_ID_MASK));
		}
		else
		{
		/* unset actionID  */
			g_pCB->ActiveActionsBitmap &= ~(1<<g_pCB->ObjPool[ObjIdx].ActionID);
		}	

    /* delete old data */
    g_pCB->ObjPool[ObjIdx].pRespArgs = NULL;
    g_pCB->ObjPool[ObjIdx].ActionID = 0;
    g_pCB->ObjPool[ObjIdx].AdditionalData = SL_MAX_SOCKETS;

    /* remove from active list */
    _SlRemoveFromList(&g_pCB->ActivePoolIdx, ObjIdx);
    /* move to free list */
    g_pCB->ObjPool[ObjIdx].NextIndex = g_pCB->FreePoolIdx;
    g_pCB->FreePoolIdx = ObjIdx;
	_SlDrvProtectionObjUnLock();
}