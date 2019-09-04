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
struct stm32_spi {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_CR1_SPE ; 
 int /*<<< orphan*/  STM32_SPI_CR1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stm32_spi_set_bits (struct stm32_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_spi_enable(struct stm32_spi *spi)
{
	dev_dbg(spi->dev, "enable controller\n");

	stm32_spi_set_bits(spi, STM32_SPI_CR1, SPI_CR1_SPE);
}