#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  numEnqueuedHW; int /*<<< orphan*/  numAllocHW; int /*<<< orphan*/  numReserveLW; int /*<<< orphan*/  numEnqueued; int /*<<< orphan*/  numAlloc; int /*<<< orphan*/  numReserved; int /*<<< orphan*/  numEnqueueOps; int /*<<< orphan*/  numDequeueOps; int /*<<< orphan*/  numFreeOps; int /*<<< orphan*/  numAllocOps; int /*<<< orphan*/ * pNext; } ;
struct TYPE_4__ {int /*<<< orphan*/  numEnqueuedHW; int /*<<< orphan*/  numAllocHW; int /*<<< orphan*/  numReserveLW; int /*<<< orphan*/  numEnqueued; int /*<<< orphan*/  numAlloc; int /*<<< orphan*/  numReserved; int /*<<< orphan*/  numEnqueueOps; int /*<<< orphan*/  numDequeueOps; int /*<<< orphan*/  numFreeOps; int /*<<< orphan*/  numAllocOps; } ;
typedef  TYPE_1__ DRV_SPI_SYS_QUEUE_STATUS ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  TYPE_2__ DRV_SPI_SYS_QUEUE_QUEUE_DATA ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_INVALID_PARAMETER ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_MAX_ERROR ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_SUCCESS ; 

DRV_SPI_SYS_QUEUE_RESULT DRV_SPI_SYS_QUEUE_QueueStatus(DRV_SPI_SYS_QUEUE_HANDLE queue, DRV_SPI_SYS_QUEUE_STATUS * status)
{
#if _SPI_DRV_SYS_QUEUE_TRACKING
    if ((queue <= 0) && (queue >= DRV_SPI_SYS_QUEUE_MAX_ERROR))
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }

    DRV_SPI_SYS_QUEUE_QUEUE_DATA * pQueue = (DRV_SPI_SYS_QUEUE_QUEUE_DATA *)queue;

    if (pQueue->pNext != NULL)
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }
    if (status == NULL)
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }

    status->numAllocOps = pQueue->numAllocOps;
    status->numFreeOps = pQueue->numFreeOps;
    status->numDequeueOps = pQueue->numDequeueOps;
    status->numEnqueueOps = pQueue->numEnqueueOps;
    status->numReserved = pQueue->numReserved;
    status->numAlloc = pQueue->numAlloc;
    status->numEnqueued = pQueue->numEnqueued;
    status->numReserveLW = pQueue->numReserveLW;
    status->numAllocHW = pQueue->numAllocHW;
    status->numEnqueuedHW = pQueue->numEnqueuedHW;
    return DRV_SPI_SYS_QUEUE_SUCCESS;
#else
    return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
#endif

}