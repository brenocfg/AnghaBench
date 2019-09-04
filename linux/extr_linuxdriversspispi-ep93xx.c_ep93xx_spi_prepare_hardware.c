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
struct spi_master {int dummy; } ;
struct ep93xx_spi {scalar_t__ mmio; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ SSPCR1 ; 
 int /*<<< orphan*/  SSPCR1_SSE ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct ep93xx_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ep93xx_spi_prepare_hardware(struct spi_master *master)
{
	struct ep93xx_spi *espi = spi_master_get_devdata(master);
	u32 val;
	int ret;

	ret = clk_enable(espi->clk);
	if (ret)
		return ret;

	val = readl(espi->mmio + SSPCR1);
	val |= SSPCR1_SSE;
	writel(val, espi->mmio + SSPCR1);

	return 0;
}