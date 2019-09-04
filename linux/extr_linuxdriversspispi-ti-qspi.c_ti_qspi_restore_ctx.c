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
struct ti_qspi_regs {int /*<<< orphan*/  clkctrl; } ;
struct ti_qspi {struct ti_qspi_regs ctx_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSPI_SPI_CLOCK_CNTRL_REG ; 
 int /*<<< orphan*/  ti_qspi_write (struct ti_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_qspi_restore_ctx(struct ti_qspi *qspi)
{
	struct ti_qspi_regs *ctx_reg = &qspi->ctx_reg;

	ti_qspi_write(qspi, ctx_reg->clkctrl, QSPI_SPI_CLOCK_CNTRL_REG);
}