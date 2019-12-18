#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {scalar_t__ baudRate; int /*<<< orphan*/ * operationEnded; int /*<<< orphan*/ * operationStarting; } ;
struct TYPE_5__ {int /*<<< orphan*/ * operationEnded; int /*<<< orphan*/ * operationStarting; } ;
typedef  TYPE_1__ DRV_SPI_OBJ ;
typedef  TYPE_2__ DRV_SPI_CLIENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_BUS_PERIPHERAL_2 ; 
 int /*<<< orphan*/  PLIB_SPI_BaudRateSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SPI_ID_1 ; 
 int /*<<< orphan*/  SYS_CLK_PeripheralFrequencyGet (int /*<<< orphan*/ ) ; 
 TYPE_1__ gDrvSPI0Obj ; 

int32_t DRV_SPI0_ClientConfigure ( const DRV_SPI_CLIENT_DATA * cfgData  )
{
    DRV_SPI_OBJ *dObj = (DRV_SPI_OBJ*)NULL;

    dObj = &gDrvSPI0Obj;

    if (cfgData == NULL)
    {
        /* Nothing to do */
        return 0;
    }

    if (cfgData->operationStarting != NULL)
    {
        dObj->operationStarting = cfgData->operationStarting;
    }

    if (cfgData->operationEnded != NULL)
    {
        dObj->operationEnded = cfgData->operationEnded;
    }

    if (cfgData->baudRate != 0)
    {

        PLIB_SPI_BaudRateSet (SPI_ID_1,
                              SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_2),
                              cfgData->baudRate);
    }

    return 0;
}