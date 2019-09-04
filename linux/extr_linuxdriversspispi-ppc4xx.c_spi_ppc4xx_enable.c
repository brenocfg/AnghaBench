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
struct ppc4xx_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDR0 ; 
 int /*<<< orphan*/  SDR0_PFC1 ; 
 int /*<<< orphan*/  dcri_clrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_ppc4xx_enable(struct ppc4xx_spi *hw)
{
	/*
	 * On all 4xx PPC's the SPI bus is shared/multiplexed with
	 * the 2nd I2C bus. We need to enable the the SPI bus before
	 * using it.
	 */

	/* need to clear bit 14 to enable SPC */
	dcri_clrset(SDR0, SDR0_PFC1, 0x80000000 >> 14, 0);
}