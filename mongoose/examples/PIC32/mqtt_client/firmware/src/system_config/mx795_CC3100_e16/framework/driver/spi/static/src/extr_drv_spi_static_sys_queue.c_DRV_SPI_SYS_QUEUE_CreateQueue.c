#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ numReserved; int /*<<< orphan*/  maxElements; int /*<<< orphan*/  fptrIntChange; TYPE_2__* pQueueManager; struct TYPE_8__* pNext; } ;
struct TYPE_7__ {scalar_t__ numReserveElements; scalar_t__ numFreeElements; scalar_t__ numQueues; scalar_t__ numQueuesHW; int /*<<< orphan*/  reserveElementsLW; int /*<<< orphan*/  numQueueCreateOps; int /*<<< orphan*/ * pFreeQueueTail; TYPE_3__* pFreeQueueHead; } ;
struct TYPE_6__ {scalar_t__ reserveElements; int /*<<< orphan*/  maxElements; int /*<<< orphan*/  fptrIntChange; } ;
typedef  TYPE_1__ DRV_SPI_SYS_QUEUE_SETUP ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  TYPE_2__ DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA ;
typedef  TYPE_3__ DRV_SPI_SYS_QUEUE_QUEUE_DATA ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_MANAGER_HANDLE ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_INVALID_PARAMETER ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_MAX_ERROR ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_OUT_OF_QUEUES ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

DRV_SPI_SYS_QUEUE_RESULT DRV_SPI_SYS_QUEUE_CreateQueue(DRV_SPI_SYS_QUEUE_MANAGER_HANDLE queueManager, DRV_SPI_SYS_QUEUE_SETUP * initParams, DRV_SPI_SYS_QUEUE_HANDLE * handle)
{
    if ((queueManager <= 0) && (queueManager >= DRV_SPI_SYS_QUEUE_MAX_ERROR))
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }
    DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA * pQueueManager = (DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA *)queueManager;
    if (initParams == NULL)
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }
    if (pQueueManager->pFreeQueueHead == NULL)
    {
        return DRV_SPI_SYS_QUEUE_OUT_OF_QUEUES;
    }

    if ((pQueueManager->numReserveElements + initParams->reserveElements) > pQueueManager->numFreeElements)
    {
        return DRV_SPI_SYS_QUEUE_OUT_OF_MEMORY;
    }

    DRV_SPI_SYS_QUEUE_QUEUE_DATA * pQueue = pQueueManager->pFreeQueueHead;
    pQueueManager->pFreeQueueHead = pQueue->pNext;
    if (pQueueManager->pFreeQueueHead == NULL)
    {
        pQueueManager->pFreeQueueTail = NULL;
    }
    memset(pQueue, 0, sizeof(DRV_SPI_SYS_QUEUE_QUEUE_DATA));
    pQueue->pQueueManager = pQueueManager;

    pQueue->fptrIntChange = initParams->fptrIntChange;
    pQueue->numReserved = initParams->reserveElements;
    pQueue->maxElements = initParams->maxElements;

    pQueueManager->numReserveElements += initParams->reserveElements;

#if _SPI_DRV_SYS_QUEUE_TRACKING
    pQueueManager->numQueueCreateOps++;
    pQueueManager->numQueues++;
    pQueueManager->reserveElementsLW += initParams->reserveElements;
    if (pQueueManager->numQueues > pQueueManager->numQueuesHW)
    {
        pQueueManager->numQueuesHW = pQueueManager->numQueues;
    }
#endif

   *handle =  (DRV_SPI_SYS_QUEUE_HANDLE)pQueue;
   return DRV_SPI_SYS_QUEUE_SUCCESS;
}