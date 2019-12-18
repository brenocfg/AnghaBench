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
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_SETUP ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_RESULT ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_MANAGER_HANDLE ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_HANDLE ;

/* Variables and functions */
 scalar_t__ DRV_SPI_SYS_QUEUE_CreateQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_SUCCESS ; 
 scalar_t__ _DRV_SPI_SYS_QUEUE_LockQueueManager (int /*<<< orphan*/ ) ; 
 scalar_t__ _DRV_SPI_SYS_QUEUE_UnlockQueueManager (int /*<<< orphan*/ ) ; 

DRV_SPI_SYS_QUEUE_HANDLE DRV_SPI_SYS_QUEUE_CreateQueueLock(DRV_SPI_SYS_QUEUE_MANAGER_HANDLE queueManager, DRV_SPI_SYS_QUEUE_SETUP * initParams, DRV_SPI_SYS_QUEUE_HANDLE * queue)
{
    DRV_SPI_SYS_QUEUE_RESULT ret;
    DRV_SPI_SYS_QUEUE_HANDLE  ret2;
    ret = _DRV_SPI_SYS_QUEUE_LockQueueManager(queueManager);
    if (ret != DRV_SPI_SYS_QUEUE_SUCCESS)
    {
        return ret;
    }

    ret2 = DRV_SPI_SYS_QUEUE_CreateQueue(queueManager, initParams, queue);

    ret = _DRV_SPI_SYS_QUEUE_UnlockQueueManager(queueManager);
    if (ret != DRV_SPI_SYS_QUEUE_SUCCESS)
    {
        return ret;
    }
    return ret2;
}