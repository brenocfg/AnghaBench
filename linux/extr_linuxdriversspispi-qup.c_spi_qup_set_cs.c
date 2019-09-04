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
typedef  int /*<<< orphan*/  u32 ;
struct spi_qup {scalar_t__ base; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 scalar_t__ SPI_IO_CONTROL ; 
 int /*<<< orphan*/  SPI_IO_C_FORCE_CS ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct spi_qup* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void spi_qup_set_cs(struct spi_device *spi, bool val)
{
	struct spi_qup *controller;
	u32 spi_ioc;
	u32 spi_ioc_orig;

	controller = spi_master_get_devdata(spi->master);
	spi_ioc = readl_relaxed(controller->base + SPI_IO_CONTROL);
	spi_ioc_orig = spi_ioc;
	if (!val)
		spi_ioc |= SPI_IO_C_FORCE_CS;
	else
		spi_ioc &= ~SPI_IO_C_FORCE_CS;

	if (spi_ioc != spi_ioc_orig)
		writel_relaxed(spi_ioc, controller->base + SPI_IO_CONTROL);
}