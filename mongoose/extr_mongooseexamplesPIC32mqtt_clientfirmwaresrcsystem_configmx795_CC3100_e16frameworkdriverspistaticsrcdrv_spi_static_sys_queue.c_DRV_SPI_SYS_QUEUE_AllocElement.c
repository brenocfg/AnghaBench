#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {struct TYPE_6__* pNext; } ;
struct TYPE_5__ {scalar_t__ numAlloc; scalar_t__ maxElements; scalar_t__ numReserved; int /*<<< orphan*/ * pNext; TYPE_1__* pQueueManager; } ;
struct TYPE_4__ {scalar_t__ numReserveElements; scalar_t__ numFreeElements; int /*<<< orphan*/ * pFreeElementTail; TYPE_3__* pFreeElementHead; } ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  TYPE_1__ DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA ;
typedef  TYPE_2__ DRV_SPI_SYS_QUEUE_QUEUE_DATA ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_HANDLE ;
typedef  TYPE_3__ DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_INVALID_PARAMETER ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_MAX_ERROR ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_SUCCESS ; 

DRV_SPI_SYS_QUEUE_RESULT DRV_SPI_SYS_QUEUE_AllocElement(DRV_SPI_SYS_QUEUE_HANDLE queue, void ** element)
{
    if (element == NULL)
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }
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

    if (pQueueManager->pFreeElementHead== NULL)
    {
#if _SPI_DRV_SYS_QUEUE_TRACKING
        pQueueManager->outOfMemoryErrors++;
        pQueue->outOfMemoryErrors++;
#endif
        return DRV_SPI_SYS_QUEUE_OUT_OF_MEMORY;
    }

    if (pQueue->numAlloc == pQueue->maxElements)
    {
#if _SPI_DRV_SYS_QUEUE_TRACKING
        pQueueManager->outOfMemoryErrors++;
        pQueue->outOfMemoryErrors++;
#endif
        return DRV_SPI_SYS_QUEUE_OUT_OF_MEMORY;
    }

    if (pQueue->numAlloc < pQueue->numReserved)
    {
        pQueueManager->numReserveElements--;
    }
    else if (pQueueManager->numFreeElements == pQueueManager->numReserveElements)
    {
#if _SPI_DRV_SYS_QUEUE_TRACKING
        pQueueManager->outOfMemoryErrors++;
        pQueue->outOfMemoryErrors++;
#endif
        return DRV_SPI_SYS_QUEUE_OUT_OF_MEMORY;
    }

    DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA * pEntry = pQueueManager->pFreeElementHead;
    pQueueManager->pFreeElementHead = pEntry->pNext;
    if (pQueueManager->pFreeElementHead == NULL)
    {
        pQueueManager->pFreeElementTail = NULL;
    }
    pEntry->pNext = NULL;
    pQueueManager->numFreeElements --;
    pQueue->numAlloc++;

#if _SPI_DRV_SYS_QUEUE_TRACKING
    pQueue->numAllocOps ++;
    pQueueManager->numAllocOps ++;
    if (pQueueManager->numFreeElements < pQueueManager->freeElementsLW)
    {
        pQueueManager->freeElementsLW = pQueueManager->numFreeElements;
    }
    if (pQueueManager->numReserveElements < pQueueManager->reserveElementsLW)
    {
        pQueueManager->reserveElementsLW = pQueueManager->numReserveElements;
    }
    if (pQueue->numAlloc > pQueue->numAllocHW)
    {
        pQueue->numAllocHW = pQueue->numAlloc;
    }
#endif
    *element = (void *)((uint32_t)pEntry + sizeof(DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA));
    return DRV_SPI_SYS_QUEUE_SUCCESS;
}