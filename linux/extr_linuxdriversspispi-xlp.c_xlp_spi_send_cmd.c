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
struct xlp_spi_priv {int /*<<< orphan*/  cs; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLP_SPI_CMD ; 
 int XLP_SPI_CMD_CONT ; 
 int XLP_SPI_CMD_RX_MASK ; 
 int XLP_SPI_CMD_TX_MASK ; 
 int XLP_SPI_XFR_BITCNT_SHIFT ; 
 int /*<<< orphan*/  xlp_spi_reg_write (struct xlp_spi_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlp_spi_send_cmd(struct xlp_spi_priv *xspi, int xfer_len,
			int cmd_cont)
{
	u32 cmd = 0;

	if (xspi->tx_buf)
		cmd |= XLP_SPI_CMD_TX_MASK;
	if (xspi->rx_buf)
		cmd |= XLP_SPI_CMD_RX_MASK;
	if (cmd_cont)
		cmd |= XLP_SPI_CMD_CONT;
	cmd |= ((xfer_len * 8 - 1) << XLP_SPI_XFR_BITCNT_SHIFT);
	xlp_spi_reg_write(xspi, xspi->cs, XLP_SPI_CMD, cmd);
}