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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct tegra_uart_port {int fcr_shadow; int ier_shadow; int rx_in_progress; TYPE_1__ uport; scalar_t__ lcr_shadow; scalar_t__ tx_in_progress; int /*<<< orphan*/  rst; int /*<<< orphan*/  uart_clk; scalar_t__ current_baud; scalar_t__ mcr_shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_UART_DEFAULT_BAUD ; 
 scalar_t__ TEGRA_UART_DEFAULT_LSR ; 
 int TEGRA_UART_IER_EORD ; 
 int TEGRA_UART_TX_TRIG_16B ; 
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_DMA_SELECT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int UART_FCR_R_TRIG_01 ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RLSI ; 
 int UART_IER_RTOIE ; 
 int /*<<< orphan*/  UART_SCR ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_set_baudrate (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_uart_read (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int tegra_uart_start_rx_dma (struct tegra_uart_port*) ; 
 int /*<<< orphan*/  tegra_uart_wait_cycle_time (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  tegra_uart_write (struct tegra_uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra_uart_hw_init(struct tegra_uart_port *tup)
{
	int ret;

	tup->fcr_shadow = 0;
	tup->mcr_shadow = 0;
	tup->lcr_shadow = 0;
	tup->ier_shadow = 0;
	tup->current_baud = 0;

	clk_prepare_enable(tup->uart_clk);

	/* Reset the UART controller to clear all previous status.*/
	reset_control_assert(tup->rst);
	udelay(10);
	reset_control_deassert(tup->rst);

	tup->rx_in_progress = 0;
	tup->tx_in_progress = 0;

	/*
	 * Set the trigger level
	 *
	 * For PIO mode:
	 *
	 * For receive, this will interrupt the CPU after that many number of
	 * bytes are received, for the remaining bytes the receive timeout
	 * interrupt is received. Rx high watermark is set to 4.
	 *
	 * For transmit, if the trasnmit interrupt is enabled, this will
	 * interrupt the CPU when the number of entries in the FIFO reaches the
	 * low watermark. Tx low watermark is set to 16 bytes.
	 *
	 * For DMA mode:
	 *
	 * Set the Tx trigger to 16. This should match the DMA burst size that
	 * programmed in the DMA registers.
	 */
	tup->fcr_shadow = UART_FCR_ENABLE_FIFO;
	tup->fcr_shadow |= UART_FCR_R_TRIG_01;
	tup->fcr_shadow |= TEGRA_UART_TX_TRIG_16B;
	tegra_uart_write(tup, tup->fcr_shadow, UART_FCR);

	/* Dummy read to ensure the write is posted */
	tegra_uart_read(tup, UART_SCR);

	/*
	 * For all tegra devices (up to t210), there is a hardware issue that
	 * requires software to wait for 3 UART clock periods after enabling
	 * the TX fifo, otherwise data could be lost.
	 */
	tegra_uart_wait_cycle_time(tup, 3);

	/*
	 * Initialize the UART with default configuration
	 * (115200, N, 8, 1) so that the receive DMA buffer may be
	 * enqueued
	 */
	tup->lcr_shadow = TEGRA_UART_DEFAULT_LSR;
	tegra_set_baudrate(tup, TEGRA_UART_DEFAULT_BAUD);
	tup->fcr_shadow |= UART_FCR_DMA_SELECT;
	tegra_uart_write(tup, tup->fcr_shadow, UART_FCR);

	ret = tegra_uart_start_rx_dma(tup);
	if (ret < 0) {
		dev_err(tup->uport.dev, "Not able to start Rx DMA\n");
		return ret;
	}
	tup->rx_in_progress = 1;

	/*
	 * Enable IE_RXS for the receive status interrupts like line errros.
	 * Enable IE_RX_TIMEOUT to get the bytes which cannot be DMA'd.
	 *
	 * If using DMA mode, enable EORD instead of receive interrupt which
	 * will interrupt after the UART is done with the receive instead of
	 * the interrupt when the FIFO "threshold" is reached.
	 *
	 * EORD is different interrupt than RX_TIMEOUT - RX_TIMEOUT occurs when
	 * the DATA is sitting in the FIFO and couldn't be transferred to the
	 * DMA as the DMA size alignment(4 bytes) is not met. EORD will be
	 * triggered when there is a pause of the incomming data stream for 4
	 * characters long.
	 *
	 * For pauses in the data which is not aligned to 4 bytes, we get
	 * both the EORD as well as RX_TIMEOUT - SW sees RX_TIMEOUT first
	 * then the EORD.
	 */
	tup->ier_shadow = UART_IER_RLSI | UART_IER_RTOIE | TEGRA_UART_IER_EORD;
	tegra_uart_write(tup, tup->ier_shadow, UART_IER);
	return 0;
}