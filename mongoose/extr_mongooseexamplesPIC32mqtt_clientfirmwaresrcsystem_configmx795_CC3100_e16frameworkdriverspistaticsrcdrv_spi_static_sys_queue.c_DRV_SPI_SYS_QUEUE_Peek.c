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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pHead; int /*<<< orphan*/ * pNext; } ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  TYPE_1__ DRV_SPI_SYS_QUEUE_QUEUE_DATA ;
typedef  scalar_t__ DRV_SPI_SYS_QUEUE_HANDLE ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_INVALID_PARAMETER ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_MAX_ERROR ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_SUCCESS ; 

DRV_SPI_SYS_QUEUE_RESULT DRV_SPI_SYS_QUEUE_Peek(DRV_SPI_SYS_QUEUE_HANDLE queue, void ** element)
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

    if (pQueue->pNext != NULL)
    {
        return DRV_SPI_SYS_QUEUE_INVALID_PARAMETER;
    }
    if (pQueue->pHead == NULL)
    {
        *element = NULL;
    }
    DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA * pEntry = pQueue->pHead;
    *element = (void *)((uint32_t)pEntry + sizeof(DRV_SPI_SYS_QUEUE_FIFO_ELEMENT_DATA));
    return DRV_SPI_SYS_QUEUE_SUCCESS;
}