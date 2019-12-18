#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* fptrIntChange ) (scalar_t__,int) ;int /*<<< orphan*/ * pNext; int /*<<< orphan*/ * pQueueManager; } ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_QUEUE_MANAGER_DATA ;
typedef  TYPE_1__ DRV_SPI_SYS_QUEUE_QUEUE_DATA ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_MANAGER_HANDLE ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_INVALID_PARAMETER ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_MAX_ERROR ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_SUCCESS ; 
 int /*<<< orphan*/  _DRV_SPI_SYS_QUEUE_LockQueueManager (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int) ; 

DRV_SPI_SYS_QUEUE_RESULT _DRV_SPI_SYS_QUEUE_LockQueue(DRV_SPI_SYS_QUEUE_HANDLE queue, bool freeList)
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

    if (freeList)
    {
        return _DRV_SPI_SYS_QUEUE_LockQueueManager((DRV_SPI_SYS_QUEUE_MANAGER_HANDLE)pQueueManager);
    }
    else
    {
        if (pQueue->fptrIntChange != NULL)
        {
            (*pQueue->fptrIntChange)(queue, true);
        }
    }

    return DRV_SPI_SYS_QUEUE_SUCCESS;
}