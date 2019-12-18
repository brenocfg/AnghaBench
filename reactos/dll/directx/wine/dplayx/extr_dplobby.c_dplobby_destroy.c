#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* DebugInfo; } ;
struct TYPE_7__ {TYPE_5__ lock; int /*<<< orphan*/  msgs; scalar_t__ msgtid; } ;
struct TYPE_6__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ IDirectPlayLobbyImpl ;

/* Variables and functions */
 int /*<<< orphan*/  DPQ_DELETEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  LPDPLMSG ; 
 int /*<<< orphan*/  cbDeleteElemFromHeap ; 
 int /*<<< orphan*/  msgs ; 

__attribute__((used)) static void dplobby_destroy(IDirectPlayLobbyImpl *obj)
{
    if ( obj->msgtid )
        FIXME( "Should kill the msg thread\n" );

    DPQ_DELETEQ( obj->msgs, msgs, LPDPLMSG, cbDeleteElemFromHeap );
    obj->lock.DebugInfo->Spare[0] = 0;
    DeleteCriticalSection( &obj->lock );
    HeapFree( GetProcessHeap(), 0, obj );
}