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
typedef  int u32 ;
struct spi_imx_data {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MX51_ECSPI_CTRL ; 
 int MX51_ECSPI_CTRL_BL_MASK ; 
 int MX51_ECSPI_CTRL_BL_OFFSET ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void spi_imx_set_burst_len(struct spi_imx_data *spi_imx, int n_bits)
{
	u32 ctrl;

	ctrl = readl(spi_imx->base + MX51_ECSPI_CTRL);
	ctrl &= ~MX51_ECSPI_CTRL_BL_MASK;
	ctrl |= ((n_bits - 1) << MX51_ECSPI_CTRL_BL_OFFSET);
	writel(ctrl, spi_imx->base + MX51_ECSPI_CTRL);
}