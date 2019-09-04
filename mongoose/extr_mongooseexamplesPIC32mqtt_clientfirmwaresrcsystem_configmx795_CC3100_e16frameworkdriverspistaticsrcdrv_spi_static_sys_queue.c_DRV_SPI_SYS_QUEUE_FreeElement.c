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
struct TYPE_5__ {scalar_t__ numAlloc; scalar_t__ numReserved; int /*<<< orphan*/ * pNext; TYPE_1__* pQueueManager; } ;
struct TYPE_4__ {int /*<<< orphan*/  numReserveElements; int /*<<< orphan*/  numFreeElements; TYPE_3__* pFreeElementTail; TYPE_3__* pFreeElementHead; } ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  TYPE_1__ DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA ;
typedef  TYPE_2__ DRV_SPI_SYS_QUEUE_QUEUE_DATA ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_HANDLE ;
typedef  TYPE_3__ DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_INVALID_PARAMETER ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_MAX_ERROR ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_SUCCESS ; 

DRV_SPI_SYS_QUEUE_RESULT DRV_SPI_SYS_QUEUE_FreeElement(DRV_SPI_SYS_QUEUE_HANDLE queue, void * element)
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

    DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA * pEntry = (DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA *)((uint32_t)element - sizeof(DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA));

    if (pQueueManager->pFreeElementHead == NULL)
    {
        pQueueManager->pFreeElementHead = pEntry;
    }
    else
    {
        pQueueManager->pFreeElementTail->pNext = pEntry;
    }
    pQueueManager->pFreeElementTail = pEntry;

    pQueueManager->numFreeElements++;
    pQueue->numAlloc--;
    if (pQueue->numAlloc < pQueue->numReserved)
    {
        pQueueManager->numReserveElements++;
    }

#if _SPI_DRV_SYS_QUEUE_TRACKING
    pQueue->numFreeOps ++;
    pQueueManager->numFreeOps ++;
#endif
    return DRV_SPI_SYS_QUEUE_SUCCESS;
}