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
struct TYPE_4__ {struct TYPE_4__* pNext; scalar_t__ numReserved; TYPE_1__* pQueueManager; } ;
struct TYPE_3__ {scalar_t__ numReserveElements; int /*<<< orphan*/  reserveElementsLW; int /*<<< orphan*/  numQueues; int /*<<< orphan*/  numQueueDestroyOps; TYPE_2__* pFreeQueueHead; TYPE_2__* pFreeQueueTail; } ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  TYPE_1__ DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA ;
typedef  TYPE_2__ DRV_SPI_SYS_QUEUE_QUEUE_DATA ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_Dequeue (scalar_t__,void**) ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_FreeElement (scalar_t__,void*) ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_INVALID_PARAMETER ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_MAX_ERROR ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_SUCCESS ; 

DRV_SPI_SYS_QUEUE_RESULT DRV_SPI_SYS_QUEUE_DestroyQueue(DRV_SPI_SYS_QUEUE_HANDLE queue)
{
    if ((queue <= 0) && (queue >= DRV_SPI_SYS_QUEUE_MAX_ERROR))
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }

    DRV_SPI_SYS_QUEUE_QUEUE_DATA * pQueue = (DRV_SPI_SYS_QUEUE_QUEUE_DATA *)queue;
    DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA * pQueueManager = pQueue->pQueueManager;

    if (pQueue->pNext != NULL)
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }


    void * pElement = NULL;
    DRV_SPI_SYS_QUEUE_Dequeue(queue, &pElement);
    while (pElement != NULL)
    {
        DRV_SPI_SYS_QUEUE_FreeElement(queue, pElement);
        DRV_SPI_SYS_QUEUE_Dequeue(queue, &pElement);
    }

    pQueueManager->numReserveElements -= pQueue->numReserved;
    if (pQueueManager->pFreeQueueTail == NULL)
    {
        pQueueManager->pFreeQueueTail = pQueue;
        pQueueManager->pFreeQueueHead = pQueue;
    }
    else
    {
        pQueue->pNext = pQueueManager->pFreeQueueHead;
        pQueueManager->pFreeQueueHead = pQueue;
    }

#if _SPI_DRV_SYS_QUEUE_TRACKING
    pQueueManager->numQueueDestroyOps++;
    pQueueManager->numQueues--;
    pQueueManager->reserveElementsLW -= pQueueManager->numReserveElements;
#endif

    return DRV_SPI_SYS_QUEUE_SUCCESS;
}