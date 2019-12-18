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

/* Variables and functions */
 scalar_t__ AR71XX_SPI_BASE ; 
 int /*<<< orphan*/  KSEG1ADDR (scalar_t__) ; 
 int /*<<< orphan*/  PRINTD (char*) ; 
 scalar_t__ SPI_REG_CTRL ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

void spi_init()
{
	PRINTD("ar71xx_spi: spi_init");

	// Init SPI Hardware, disable remap, set clock
	__raw_writel(0x43, KSEG1ADDR(AR71XX_SPI_BASE + SPI_REG_CTRL));
	
	PRINTD(" ---> out\n");
}