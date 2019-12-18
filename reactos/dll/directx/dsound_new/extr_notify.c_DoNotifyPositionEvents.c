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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_10__ {TYPE_4__* EventListHead; } ;
struct TYPE_9__ {scalar_t__ NotifyCount; struct TYPE_9__* lpNext; TYPE_3__* Notify; } ;
struct TYPE_6__ {int /*<<< orphan*/  Event; } ;
struct TYPE_7__ {TYPE_1__ EventHandle; } ;
struct TYPE_8__ {scalar_t__ Position; TYPE_2__ KsEventData; } ;
typedef  TYPE_4__* LPNOTIFYEVENT ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDNOTIFY ;
typedef  TYPE_5__* LPCDirectSoundNotifyImpl ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CDirectSoundNotifyImpl ; 
 int /*<<< orphan*/  CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpVtbl ; 

VOID
DoNotifyPositionEvents(
    LPDIRECTSOUNDNOTIFY iface,
    DWORD OldPosition,
    DWORD NewPosition)
{
    DWORD Index;
    LPNOTIFYEVENT CurEventList;

    LPCDirectSoundNotifyImpl This = (LPCDirectSoundNotifyImpl)CONTAINING_RECORD(iface, CDirectSoundNotifyImpl, lpVtbl);

    CurEventList = This->EventListHead;

    while(CurEventList)
    {
        for(Index = 0; Index < CurEventList->NotifyCount; Index++)
        {
            if (NewPosition > OldPosition)
            {
                /* buffer progress no overlap */
                if (OldPosition < CurEventList->Notify[Index].Position && CurEventList->Notify[Index].Position <= NewPosition)
                {
                    /* process event */
                    SetEvent(CurEventList->Notify[Index].KsEventData.EventHandle.Event);
                }
            }
            else
            {
                /* buffer wrap-arround */
                if (OldPosition < CurEventList->Notify[Index].Position || NewPosition > CurEventList->Notify[Index].Position)
                {
                    /* process event */
                    SetEvent(CurEventList->Notify[Index].KsEventData.EventHandle.Event);
                }
            }
        }

        /* iterate to next event list */
        CurEventList = CurEventList->lpNext;
    }
}