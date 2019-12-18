#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct DRV_SPI_DRIVER_OBJECT {int /*<<< orphan*/  vfMainTask; } ;
typedef  int int32_t ;
struct TYPE_3__ {scalar_t__ spiMode; int taskMode; scalar_t__ bufferType; scalar_t__ commWidth; } ;
typedef  TYPE_1__ DRV_SPI_INIT ;

/* Variables and functions */
 scalar_t__ DRV_SPI_BUFFER_TYPE_ENHANCED ; 
 int /*<<< orphan*/  DRV_SPI_ISRMasterEBM8BitTasks ; 
 scalar_t__ DRV_SPI_MODE_MASTER ; 
 int DRV_SPI_TASK_MODE_ISR ; 
 scalar_t__ SPI_COMMUNICATION_WIDTH_8BITS ; 
 int /*<<< orphan*/  SYS_ASSERT (int,char*) ; 
 int _SPI_DRV_VTABLE_8BIT ; 
 int _SPI_DRV_VTABLE_EBM ; 
#define  _SPI_DRV_VTABLE_I_M_E_8 128 
 int _SPI_DRV_VTABLE_MASTER ; 

int32_t DRV_SPI_SetVTable(struct DRV_SPI_DRIVER_OBJECT * driverObject, const DRV_SPI_INIT * const pInit)
{
    uint8_t mode = 0;
    if (pInit->spiMode == DRV_SPI_MODE_MASTER)
    {
        mode = _SPI_DRV_VTABLE_MASTER;
    }
    else
    {
        SYS_ASSERT(false, "\r\nInvalid SPI Configuration.");
        return -1;
    }

    if (pInit->taskMode == DRV_SPI_TASK_MODE_ISR)
    {
        mode |= DRV_SPI_TASK_MODE_ISR;
    }
    else
    {
        SYS_ASSERT(false, "\r\nInvalid SPI Configuration.");
        return -1;
    }

    if (pInit->bufferType == DRV_SPI_BUFFER_TYPE_ENHANCED)
    {
        mode |= _SPI_DRV_VTABLE_EBM;
    }
    else
    {
        SYS_ASSERT(false, "\r\nInvalid SPI Configuration.");
        return -1;
    }

    if (pInit->commWidth == SPI_COMMUNICATION_WIDTH_8BITS)
    {
        mode |= _SPI_DRV_VTABLE_8BIT;
    }
    else
    {
        SYS_ASSERT(false, "\r\nInvalid SPI Configuration.");
        return -1;
    }
    switch (mode)
    {
    case _SPI_DRV_VTABLE_I_M_E_8:
        driverObject->vfMainTask = DRV_SPI_ISRMasterEBM8BitTasks;
        break;
    default:
        SYS_ASSERT(false, "\r\nInvalid SPI Configuration.");
        return -1;
    }
    return 0;
}