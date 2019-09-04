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
struct uart_port {scalar_t__ membase; } ;
struct qcom_geni_serial_port {scalar_t__ xfer_mode; int tx_wm; } ;

/* Variables and functions */
 scalar_t__ GENI_SE_FIFO ; 
 int M_CMD_DONE_EN ; 
 int M_GENI_CMD_ACTIVE ; 
 int M_TX_FIFO_WATERMARK_EN ; 
 scalar_t__ SE_GENI_M_IRQ_EN ; 
 scalar_t__ SE_GENI_STATUS ; 
 scalar_t__ SE_GENI_TX_WATERMARK_REG ; 
 int /*<<< orphan*/  qcom_geni_serial_tx_empty (struct uart_port*) ; 
 int readl (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 struct qcom_geni_serial_port* to_dev_port (struct uart_port*,struct uart_port*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void qcom_geni_serial_start_tx(struct uart_port *uport)
{
	u32 irq_en;
	struct qcom_geni_serial_port *port = to_dev_port(uport, uport);
	u32 status;

	if (port->xfer_mode == GENI_SE_FIFO) {
		/*
		 * readl ensures reading & writing of IRQ_EN register
		 * is not re-ordered before checking the status of the
		 * Serial Engine.
		 */
		status = readl(uport->membase + SE_GENI_STATUS);
		if (status & M_GENI_CMD_ACTIVE)
			return;

		if (!qcom_geni_serial_tx_empty(uport))
			return;

		irq_en = readl_relaxed(uport->membase +	SE_GENI_M_IRQ_EN);
		irq_en |= M_TX_FIFO_WATERMARK_EN | M_CMD_DONE_EN;

		writel_relaxed(port->tx_wm, uport->membase +
						SE_GENI_TX_WATERMARK_REG);
		writel_relaxed(irq_en, uport->membase +	SE_GENI_M_IRQ_EN);
	}
}