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
struct qcom_geni_serial_port {scalar_t__ xfer_mode; int /*<<< orphan*/  se; } ;

/* Variables and functions */
 scalar_t__ GENI_SE_FIFO ; 
 int M_RX_FIFO_LAST_EN ; 
 int M_RX_FIFO_WATERMARK_EN ; 
 scalar_t__ SE_GENI_M_IRQ_EN ; 
 scalar_t__ SE_GENI_STATUS ; 
 scalar_t__ SE_GENI_S_IRQ_EN ; 
 int S_GENI_CMD_ACTIVE ; 
 int S_RX_FIFO_LAST_EN ; 
 int S_RX_FIFO_WATERMARK_EN ; 
 int /*<<< orphan*/  UART_START_READ ; 
 int /*<<< orphan*/  geni_se_setup_s_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  qcom_geni_serial_stop_rx (struct uart_port*) ; 
 int readl_relaxed (scalar_t__) ; 
 struct qcom_geni_serial_port* to_dev_port (struct uart_port*,struct uart_port*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void qcom_geni_serial_start_rx(struct uart_port *uport)
{
	u32 irq_en;
	u32 status;
	struct qcom_geni_serial_port *port = to_dev_port(uport, uport);

	status = readl_relaxed(uport->membase + SE_GENI_STATUS);
	if (status & S_GENI_CMD_ACTIVE)
		qcom_geni_serial_stop_rx(uport);

	/*
	 * Ensure setup command write is not re-ordered before checking
	 * the status of the Secondary Sequencer.
	 */
	mb();

	geni_se_setup_s_cmd(&port->se, UART_START_READ, 0);

	if (port->xfer_mode == GENI_SE_FIFO) {
		irq_en = readl_relaxed(uport->membase + SE_GENI_S_IRQ_EN);
		irq_en |= S_RX_FIFO_WATERMARK_EN | S_RX_FIFO_LAST_EN;
		writel_relaxed(irq_en, uport->membase + SE_GENI_S_IRQ_EN);

		irq_en = readl_relaxed(uport->membase + SE_GENI_M_IRQ_EN);
		irq_en |= M_RX_FIFO_WATERMARK_EN | M_RX_FIFO_LAST_EN;
		writel_relaxed(irq_en, uport->membase + SE_GENI_M_IRQ_EN);
	}
}