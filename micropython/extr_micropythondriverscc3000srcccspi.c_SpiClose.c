#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pRxPacket; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* WlanInterruptDisable ) () ;} ;

/* Variables and functions */
 TYPE_2__ sSpiInformation ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_1__ tSLInformation ; 

void SpiClose(void)
{
    if (sSpiInformation.pRxPacket) {
        sSpiInformation.pRxPacket = 0;
    }

    tSLInformation.WlanInterruptDisable();

    //HAL_SPI_DeInit(SPI_HANDLE);
}