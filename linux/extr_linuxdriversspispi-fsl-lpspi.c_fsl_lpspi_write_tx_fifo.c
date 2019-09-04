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
typedef  int u8 ;
struct fsl_lpspi_data {int txfifosize; scalar_t__ base; int /*<<< orphan*/  remain; int /*<<< orphan*/  (* tx ) (struct fsl_lpspi_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IER_TDIE ; 
 scalar_t__ IMX7ULP_FSR ; 
 scalar_t__ IMX7ULP_TDR ; 
 int /*<<< orphan*/  fsl_lpspi_intctrl (struct fsl_lpspi_data*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct fsl_lpspi_data*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fsl_lpspi_write_tx_fifo(struct fsl_lpspi_data *fsl_lpspi)
{
	u8 txfifo_cnt;

	txfifo_cnt = readl(fsl_lpspi->base + IMX7ULP_FSR) & 0xff;

	while (txfifo_cnt < fsl_lpspi->txfifosize) {
		if (!fsl_lpspi->remain)
			break;
		fsl_lpspi->tx(fsl_lpspi);
		txfifo_cnt++;
	}

	if (!fsl_lpspi->remain && (txfifo_cnt < fsl_lpspi->txfifosize))
		writel(0, fsl_lpspi->base + IMX7ULP_TDR);
	else
		fsl_lpspi_intctrl(fsl_lpspi, IER_TDIE);
}