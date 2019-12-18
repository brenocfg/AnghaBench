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
struct TYPE_5__ {int /*<<< orphan*/  numQueuesHW; int /*<<< orphan*/  numQueues; int /*<<< orphan*/  outOfMemoryErrors; int /*<<< orphan*/  reserveElementsLW; int /*<<< orphan*/  freeElementsLW; int /*<<< orphan*/  numFreeElements; int /*<<< orphan*/  numReserveElements; int /*<<< orphan*/  numQueueDestroyOps; int /*<<< orphan*/  numQueueCreateOps; int /*<<< orphan*/  numFreeOps; int /*<<< orphan*/  numAllocOps; } ;
struct TYPE_4__ {int /*<<< orphan*/  numQueuesHW; int /*<<< orphan*/  numQueues; int /*<<< orphan*/  outOfMemoryErrors; int /*<<< orphan*/  reserveElementsLW; int /*<<< orphan*/  freeElementsLW; int /*<<< orphan*/  numFreeElements; int /*<<< orphan*/  numReserveElements; int /*<<< orphan*/  numQueueDestroyOps; int /*<<< orphan*/  numQueueCreateOps; int /*<<< orphan*/  numFreeOps; int /*<<< orphan*/  numAllocOps; } ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  TYPE_1__ DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA ;
typedef  TYPE_2__ DRV_SPI_SYS_QUEUE_MANAGER_STATUS ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_MANAGER_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_INVALID_PARAMETER ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_MAX_ERROR ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_SUCCESS ; 

DRV_SPI_SYS_QUEUE_RESULT DRV_SPI_SYS_QUEUE_QueueManagerStatus(DRV_SPI_SYS_QUEUE_MANAGER_HANDLE queueManager, DRV_SPI_SYS_QUEUE_MANAGER_STATUS * status)
{
#if _SPI_DRV_SYS_QUEUE_TRACKING
    if ((queueManager <= 0) && (queueManager >= DRV_SPI_SYS_QUEUE_MAX_ERROR))
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }
    DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA * pQueueManager = (DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA *)queueManager;

    status->numAllocOps = pQueueManager->numAllocOps;
    status->numFreeOps = pQueueManager->numFreeOps;
    status->numQueueCreateOps = pQueueManager->numQueueCreateOps;
    status->numQueueDestroyOps = pQueueManager->numQueueDestroyOps;
    status->numReserveElements = pQueueManager->numReserveElements;
    status->numFreeElements = pQueueManager->numFreeElements;
    status->freeElementsLW = pQueueManager->freeElementsLW;
    status->reserveElementsLW = pQueueManager->reserveElementsLW;
    status->outOfMemoryErrors = pQueueManager->outOfMemoryErrors;
    status->numQueues = pQueueManager->numQueues;
    status->numQueuesHW = pQueueManager->numQueuesHW;
    return DRV_SPI_SYS_QUEUE_SUCCESS;
#else
    return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
#endif
}