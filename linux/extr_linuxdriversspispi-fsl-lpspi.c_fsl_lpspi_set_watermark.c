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
struct fsl_lpspi_data {int txfifosize; int rxfifosize; int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IMX7ULP_FCR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void fsl_lpspi_set_watermark(struct fsl_lpspi_data *fsl_lpspi)
{
	u32 temp;

	temp = fsl_lpspi->txfifosize >> 1 | (fsl_lpspi->rxfifosize >> 1) << 16;

	writel(temp, fsl_lpspi->base + IMX7ULP_FCR);

	dev_dbg(fsl_lpspi->dev, "FCR=0x%x\n", temp);
}