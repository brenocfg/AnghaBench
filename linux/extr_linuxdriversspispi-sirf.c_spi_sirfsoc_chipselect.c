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
typedef  int /*<<< orphan*/  u32 ;
struct spi_device {int mode; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  master; } ;
struct sirfsoc_spi {int type; TYPE_1__* regs; scalar_t__ base; scalar_t__ hw_cs; } ;
struct TYPE_2__ {scalar_t__ usp_pin_io_data; scalar_t__ spi_ctrl; } ;

/* Variables and functions */
#define  BITBANG_CS_ACTIVE 132 
#define  BITBANG_CS_INACTIVE 131 
 int /*<<< orphan*/  SIRFSOC_SPI_CS_IO_OUT ; 
 int /*<<< orphan*/  SIRFSOC_USP_CS_HIGH_VALUE ; 
#define  SIRF_REAL_SPI 130 
#define  SIRF_USP_SPI_A7 129 
#define  SIRF_USP_SPI_P2 128 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct sirfsoc_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void spi_sirfsoc_chipselect(struct spi_device *spi, int value)
{
	struct sirfsoc_spi *sspi = spi_master_get_devdata(spi->master);

	if (sspi->hw_cs) {
		u32 regval;

		switch (sspi->type) {
		case SIRF_REAL_SPI:
			regval = readl(sspi->base + sspi->regs->spi_ctrl);
			switch (value) {
			case BITBANG_CS_ACTIVE:
				if (spi->mode & SPI_CS_HIGH)
					regval |= SIRFSOC_SPI_CS_IO_OUT;
				else
					regval &= ~SIRFSOC_SPI_CS_IO_OUT;
				break;
			case BITBANG_CS_INACTIVE:
				if (spi->mode & SPI_CS_HIGH)
					regval &= ~SIRFSOC_SPI_CS_IO_OUT;
				else
					regval |= SIRFSOC_SPI_CS_IO_OUT;
				break;
			}
			writel(regval, sspi->base + sspi->regs->spi_ctrl);
			break;
		case SIRF_USP_SPI_P2:
		case SIRF_USP_SPI_A7:
			regval = readl(sspi->base +
					sspi->regs->usp_pin_io_data);
			switch (value) {
			case BITBANG_CS_ACTIVE:
				if (spi->mode & SPI_CS_HIGH)
					regval |= SIRFSOC_USP_CS_HIGH_VALUE;
				else
					regval &= ~(SIRFSOC_USP_CS_HIGH_VALUE);
				break;
			case BITBANG_CS_INACTIVE:
				if (spi->mode & SPI_CS_HIGH)
					regval &= ~(SIRFSOC_USP_CS_HIGH_VALUE);
				else
					regval |= SIRFSOC_USP_CS_HIGH_VALUE;
				break;
			}
			writel(regval,
				sspi->base + sspi->regs->usp_pin_io_data);
			break;
		}
	} else {
		switch (value) {
		case BITBANG_CS_ACTIVE:
			gpio_direction_output(spi->cs_gpio,
					spi->mode & SPI_CS_HIGH ? 1 : 0);
			break;
		case BITBANG_CS_INACTIVE:
			gpio_direction_output(spi->cs_gpio,
					spi->mode & SPI_CS_HIGH ? 0 : 1);
			break;
		}
	}
}