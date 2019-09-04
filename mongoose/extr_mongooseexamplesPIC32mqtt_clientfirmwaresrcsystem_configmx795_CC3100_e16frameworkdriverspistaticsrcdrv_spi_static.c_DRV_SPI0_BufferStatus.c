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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ DRV_SPI_JOB_OBJECT ;
typedef  scalar_t__ DRV_SPI_BUFFER_HANDLE ;
typedef  int /*<<< orphan*/  DRV_SPI_BUFFER_EVENT ;

/* Variables and functions */

DRV_SPI_BUFFER_EVENT DRV_SPI0_BufferStatus ( DRV_SPI_BUFFER_HANDLE bufferHandle )
{
    DRV_SPI_JOB_OBJECT * pJob = (DRV_SPI_JOB_OBJECT *)bufferHandle;

    return pJob->status;
}