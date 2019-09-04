#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_STATUS ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_INVALID_PARAMETER ; 

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