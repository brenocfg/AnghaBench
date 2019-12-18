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
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_RESULT ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_HANDLE ;

/* Variables and functions */
 scalar_t__ DRV_SPI_SYS_QUEUE_DestroyQueue (int /*<<< orphan*/ ) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_SUCCESS ; 
 scalar_t__ _DRV_SPI_SYS_QUEUE_LockQueue (int /*<<< orphan*/ ,int) ; 
 scalar_t__ _DRV_SPI_SYS_QUEUE_UnlockQueue (int /*<<< orphan*/ ,int) ; 

DRV_SPI_SYS_QUEUE_RESULT DRV_SPI_SYS_QUEUE_DestroyQueueLock(DRV_SPI_SYS_QUEUE_HANDLE queue)
{
    DRV_SPI_SYS_QUEUE_RESULT ret;
    DRV_SPI_SYS_QUEUE_RESULT  ret2;
    ret = _DRV_SPI_SYS_QUEUE_LockQueue(queue, true);// TODO!!! Fix this
    if (ret != DRV_SPI_SYS_QUEUE_SUCCESS)
    {
        return ret;
    }

    ret2 = DRV_SPI_SYS_QUEUE_DestroyQueue(queue);

    ret = _DRV_SPI_SYS_QUEUE_UnlockQueue(queue, true);
    if (ret != DRV_SPI_SYS_QUEUE_SUCCESS)
    {
        return ret;
    }
    return ret2;
}