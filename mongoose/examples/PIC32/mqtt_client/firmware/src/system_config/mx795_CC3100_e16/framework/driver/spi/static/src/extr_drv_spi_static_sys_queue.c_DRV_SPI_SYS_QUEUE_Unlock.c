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
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_RESULT ;
typedef  int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  _DRV_SPI_SYS_QUEUE_UnlockQueue (int /*<<< orphan*/ ,int) ; 

DRV_SPI_SYS_QUEUE_RESULT DRV_SPI_SYS_QUEUE_Unlock(DRV_SPI_SYS_QUEUE_HANDLE queue)
{
    return _DRV_SPI_SYS_QUEUE_UnlockQueue(queue, false);
}