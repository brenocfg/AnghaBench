#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* DebugInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_7__ cs; int /*<<< orphan*/  cmdQueue; TYPE_1__ impl; TYPE_3__* transport; int /*<<< orphan*/  shuttingDown; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* cleanupAdapter ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {scalar_t__* Spare; } ;
typedef  TYPE_4__ NetBIOSAdapter ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_7__*) ; 
 int /*<<< orphan*/  NBCmdQueueCancelAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBCmdQueueDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nbShutdownAdapter(NetBIOSAdapter *adapter)
{
    if (adapter)
    {
        adapter->shuttingDown = TRUE;
        NBCmdQueueCancelAll(adapter->cmdQueue);
        if (adapter->transport->cleanupAdapter)
            adapter->transport->cleanupAdapter(adapter->impl.data);
        NBCmdQueueDestroy(adapter->cmdQueue);
        adapter->cs.DebugInfo->Spare[0] = 0;
        DeleteCriticalSection(&adapter->cs);
        memset(adapter, 0, sizeof(NetBIOSAdapter));
    }
}