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
struct spi_imx_data {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MX51_ECSPI_CTRL ; 
 int /*<<< orphan*/  MX51_ECSPI_CTRL_ENABLE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mx51_ecspi_disable(struct spi_imx_data *spi_imx)
{
	u32 ctrl;

	ctrl = readl(spi_imx->base + MX51_ECSPI_CTRL);
	ctrl &= ~MX51_ECSPI_CTRL_ENABLE;
	writel(ctrl, spi_imx->base + MX51_ECSPI_CTRL);
}