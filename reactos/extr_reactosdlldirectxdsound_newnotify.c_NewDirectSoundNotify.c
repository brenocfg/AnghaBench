#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ref; int /*<<< orphan*/ * lpVtbl; int /*<<< orphan*/  BufferSize; int /*<<< orphan*/ * EventListHead; int /*<<< orphan*/  hPin; void* bMix; void* bLoop; } ;
typedef  scalar_t__ LPDIRECTSOUNDNOTIFY ;
typedef  TYPE_1__* LPCDirectSoundNotifyImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CDirectSoundNotifyImpl ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vt_DirectSoundNotify ; 

HRESULT
NewDirectSoundNotify(
    LPDIRECTSOUNDNOTIFY * Notify,
    BOOL bLoop,
    BOOL bMix,
    HANDLE hPin,
    DWORD BufferSize)
{
    LPCDirectSoundNotifyImpl This = HeapAlloc(GetProcessHeap(), 0, sizeof(CDirectSoundNotifyImpl));

    if (!This)
        return DSERR_OUTOFMEMORY;

    This->lpVtbl = &vt_DirectSoundNotify;
    This->bLoop = bLoop;
    This->bMix = bMix;
    This->hPin = hPin;
    This->ref = 1;
    This->EventListHead = NULL;
    This->BufferSize = BufferSize;

    *Notify = (LPDIRECTSOUNDNOTIFY)&This->lpVtbl;
    return DS_OK;

}