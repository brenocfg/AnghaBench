#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_2__ icount; scalar_t__ membase; scalar_t__ suspended; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct qcom_geni_serial_port {int brk; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int M_CMD_DONE_EN ; 
 unsigned int M_ILLEGAL_CMD_EN ; 
 unsigned int M_TX_FIFO_WATERMARK_EN ; 
 scalar_t__ SE_GENI_M_IRQ_CLEAR ; 
 scalar_t__ SE_GENI_M_IRQ_EN ; 
 scalar_t__ SE_GENI_M_IRQ_STATUS ; 
 scalar_t__ SE_GENI_S_IRQ_CLEAR ; 
 scalar_t__ SE_GENI_S_IRQ_STATUS ; 
 unsigned int S_GP_IRQ_0_EN ; 
 unsigned int S_GP_IRQ_1_EN ; 
 unsigned int S_GP_IRQ_2_EN ; 
 unsigned int S_GP_IRQ_3_EN ; 
 unsigned int S_RX_FIFO_LAST_EN ; 
 unsigned int S_RX_FIFO_WATERMARK_EN ; 
 unsigned int S_RX_FIFO_WR_ERR_EN ; 
 int /*<<< orphan*/  TTY_OVERRUN ; 
 scalar_t__ WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  qcom_geni_serial_handle_rx (struct uart_port*,int) ; 
 int /*<<< orphan*/  qcom_geni_serial_handle_tx (struct uart_port*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct qcom_geni_serial_port* to_dev_port (struct uart_port*,struct uart_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t qcom_geni_serial_isr(int isr, void *dev)
{
	unsigned int m_irq_status;
	unsigned int s_irq_status;
	struct uart_port *uport = dev;
	unsigned long flags;
	unsigned int m_irq_en;
	bool drop_rx = false;
	struct tty_port *tport = &uport->state->port;
	struct qcom_geni_serial_port *port = to_dev_port(uport, uport);

	if (uport->suspended)
		return IRQ_NONE;

	spin_lock_irqsave(&uport->lock, flags);
	m_irq_status = readl_relaxed(uport->membase + SE_GENI_M_IRQ_STATUS);
	s_irq_status = readl_relaxed(uport->membase + SE_GENI_S_IRQ_STATUS);
	m_irq_en = readl_relaxed(uport->membase + SE_GENI_M_IRQ_EN);
	writel_relaxed(m_irq_status, uport->membase + SE_GENI_M_IRQ_CLEAR);
	writel_relaxed(s_irq_status, uport->membase + SE_GENI_S_IRQ_CLEAR);

	if (WARN_ON(m_irq_status & M_ILLEGAL_CMD_EN))
		goto out_unlock;

	if (s_irq_status & S_RX_FIFO_WR_ERR_EN) {
		uport->icount.overrun++;
		tty_insert_flip_char(tport, 0, TTY_OVERRUN);
	}

	if (m_irq_status & (M_TX_FIFO_WATERMARK_EN | M_CMD_DONE_EN) &&
	    m_irq_en & (M_TX_FIFO_WATERMARK_EN | M_CMD_DONE_EN))
		qcom_geni_serial_handle_tx(uport);

	if (s_irq_status & S_GP_IRQ_0_EN || s_irq_status & S_GP_IRQ_1_EN) {
		if (s_irq_status & S_GP_IRQ_0_EN)
			uport->icount.parity++;
		drop_rx = true;
	} else if (s_irq_status & S_GP_IRQ_2_EN ||
					s_irq_status & S_GP_IRQ_3_EN) {
		uport->icount.brk++;
		port->brk = true;
	}

	if (s_irq_status & S_RX_FIFO_WATERMARK_EN ||
					s_irq_status & S_RX_FIFO_LAST_EN)
		qcom_geni_serial_handle_rx(uport, drop_rx);

out_unlock:
	spin_unlock_irqrestore(&uport->lock, flags);
	return IRQ_HANDLED;
}