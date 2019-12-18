#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
struct TYPE_18__ {TYPE_2__ impl; TYPE_1__* transport; } ;
struct TYPE_17__ {TYPE_4__* DebugInfo; } ;
struct TYPE_16__ {size_t tableSize; TYPE_8__* table; TYPE_7__ cs; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* cleanup ) () ;} ;
struct TYPE_15__ {TYPE_3__ transport; } ;
struct TYPE_14__ {scalar_t__* Spare; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* cleanupAdapter ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_7__*) ; 
 int /*<<< orphan*/  EnterCriticalSection (TYPE_7__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  LeaveCriticalSection (TYPE_7__*) ; 
 TYPE_6__ gNBTable ; 
 size_t gNumTransports ; 
 TYPE_5__* gTransports ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 

void NetBIOSShutdown(void)
{
    UCHAR i;

    EnterCriticalSection(&gNBTable.cs);
    for (i = 0; i < gNBTable.tableSize; i++)
    {
        if (gNBTable.table[i].transport &&
         gNBTable.table[i].transport->cleanupAdapter)
            gNBTable.table[i].transport->cleanupAdapter(
             gNBTable.table[i].impl.data);
    }
    for (i = 0; i < gNumTransports; i++)
        if (gTransports[i].transport.cleanup)
            gTransports[i].transport.cleanup();
    LeaveCriticalSection(&gNBTable.cs);
    gNBTable.cs.DebugInfo->Spare[0] = 0;
    DeleteCriticalSection(&gNBTable.cs);
    HeapFree(GetProcessHeap(), 0, gNBTable.table);
}