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
struct spi_imx_data {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MX51_ECSPI_INT ; 
 unsigned int MX51_ECSPI_INT_RDREN ; 
 unsigned int MX51_ECSPI_INT_RREN ; 
 unsigned int MX51_ECSPI_INT_TEEN ; 
 int MXC_INT_RDR ; 
 int MXC_INT_RR ; 
 int MXC_INT_TE ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mx51_ecspi_intctrl(struct spi_imx_data *spi_imx, int enable)
{
	unsigned val = 0;

	if (enable & MXC_INT_TE)
		val |= MX51_ECSPI_INT_TEEN;

	if (enable & MXC_INT_RR)
		val |= MX51_ECSPI_INT_RREN;

	if (enable & MXC_INT_RDR)
		val |= MX51_ECSPI_INT_RDREN;

	writel(val, spi_imx->base + MX51_ECSPI_INT);
}