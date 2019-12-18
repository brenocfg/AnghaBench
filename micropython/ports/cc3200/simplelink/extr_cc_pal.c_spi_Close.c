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
typedef  int /*<<< orphan*/  Fd_t ;

/* Variables and functions */
 unsigned long LSPI_BASE ; 
 int /*<<< orphan*/  MAP_PRCMPeripheralClkDisable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAP_SPICSDisable (unsigned long) ; 
 int /*<<< orphan*/  MAP_SPIDisable (unsigned long) ; 
 int /*<<< orphan*/  MAP_SPIReset (unsigned long) ; 
 int /*<<< orphan*/  PRCM_LSPI ; 
 int PRCM_RUN_MODE_CLK ; 
 int PRCM_SLP_MODE_CLK ; 
 scalar_t__ g_SpiFd ; 

int spi_Close(Fd_t fd)
{
    unsigned long ulBase = LSPI_BASE;

    g_SpiFd = 0;

		//Disable Chip Select
	MAP_SPICSDisable(LSPI_BASE);


		//Disable SPI Channel
	MAP_SPIDisable(ulBase);

		// Reset SPI
	MAP_SPIReset(ulBase);

		// Disable SPI Peripheral
	MAP_PRCMPeripheralClkDisable(PRCM_LSPI,PRCM_RUN_MODE_CLK | PRCM_SLP_MODE_CLK);

    return 0;
}