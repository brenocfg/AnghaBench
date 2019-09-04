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
 int M_CMD_ABORT_EN ; 
 int M_CMD_CANCEL_EN ; 
 int M_CMD_DONE_EN ; 
 int M_GENI_CMD_ACTIVE ; 
 int M_TX_FIFO_WATERMARK_EN ; 
 scalar_t__ SE_GENI_M_IRQ_CLEAR ; 
 scalar_t__ SE_GENI_M_IRQ_EN ; 
 int /*<<< orphan*/  SE_GENI_M_IRQ_STATUS ; 
 scalar_t__ SE_GENI_STATUS ; 
 scalar_t__ SE_GENI_TX_WATERMARK_REG ; 
 int /*<<< orphan*/  geni_se_abort_m_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geni_se_cancel_m_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  qcom_geni_serial_poll_bit (struct uart_port*,int /*<<< orphan*/ ,int,int) ; 
 int readl_relaxed (scalar_t__) ; 
 struct qcom_geni_serial_port* to_dev_port (struct uart_port*,struct uart_port*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void qcom_geni_serial_stop_tx(struct uart_port *uport)
{
	u32 irq_en;
	u32 status;
	struct qcom_geni_serial_port *port = to_dev_port(uport, uport);

	irq_en = readl_relaxed(uport->membase + SE_GENI_M_IRQ_EN);
	irq_en &= ~M_CMD_DONE_EN;
	if (port->xfer_mode == GENI_SE_FIFO) {
		irq_en &= ~M_TX_FIFO_WATERMARK_EN;
		writel_relaxed(0, uport->membase +
				     SE_GENI_TX_WATERMARK_REG);
	}
	writel_relaxed(irq_en, uport->membase + SE_GENI_M_IRQ_EN);
	status = readl_relaxed(uport->membase + SE_GENI_STATUS);
	/* Possible stop tx is called multiple times. */
	if (!(status & M_GENI_CMD_ACTIVE))
		return;

	/*
	 * Ensure cancel command write is not re-ordered before checking
	 * the status of the Primary Sequencer.
	 */
	mb();

	geni_se_cancel_m_cmd(&port->se);
	if (!qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
						M_CMD_CANCEL_EN, true)) {
		geni_se_abort_m_cmd(&port->se);
		qcom_geni_serial_poll_bit(uport, SE_GENI_M_IRQ_STATUS,
						M_CMD_ABORT_EN, true);
		writel_relaxed(M_CMD_ABORT_EN, uport->membase +
							SE_GENI_M_IRQ_CLEAR);
	}
	writel_relaxed(M_CMD_CANCEL_EN, uport->membase + SE_GENI_M_IRQ_CLEAR);
}