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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct mdev_state {TYPE_2__* s; int /*<<< orphan*/  rxtx_lock; } ;
struct TYPE_3__ {size_t head; size_t tail; int* fifo; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int divisor; int* uart_reg; int /*<<< orphan*/  max_fifo_size; TYPE_1__ rxtx; int /*<<< orphan*/  overrun; int /*<<< orphan*/  intr_trigger_level; int /*<<< orphan*/  dlab; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRCULAR_BUF_INC_IDX (size_t) ; 
#define  UART_IER 135 
 int UART_IER_MSI ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int UART_IER_THRI ; 
#define  UART_IIR 134 
 int UART_IIR_MSI ; 
 int UART_IIR_NO_INT ; 
 int UART_IIR_RDI ; 
 int UART_IIR_RLSI ; 
 int UART_IIR_THRI ; 
#define  UART_LCR 133 
#define  UART_LSR 132 
 int UART_LSR_DR ; 
 int UART_LSR_OE ; 
 int UART_LSR_TEMT ; 
 int UART_LSR_THRE ; 
#define  UART_MCR 131 
 int UART_MCR_AFE ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
#define  UART_MSR 130 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DCTS ; 
 int UART_MSR_DDSR ; 
 int UART_MSR_DSR ; 
#define  UART_RX 129 
#define  UART_SCR 128 
 int /*<<< orphan*/  mtty_trigger_interrupt (struct mdev_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static void handle_bar_read(unsigned int index, struct mdev_state *mdev_state,
			    u16 offset, u8 *buf, u32 count)
{
	/* Handle read requests by guest */
	switch (offset) {
	case UART_RX:
		/* if DLAB set, data is LSB of divisor */
		if (mdev_state->s[index].dlab) {
			*buf  = (u8)mdev_state->s[index].divisor;
			break;
		}

		mutex_lock(&mdev_state->rxtx_lock);
		/* return data in tx buffer */
		if (mdev_state->s[index].rxtx.head !=
				 mdev_state->s[index].rxtx.tail) {
			*buf = mdev_state->s[index].rxtx.fifo[
						mdev_state->s[index].rxtx.tail];
			mdev_state->s[index].rxtx.count--;
			CIRCULAR_BUF_INC_IDX(mdev_state->s[index].rxtx.tail);
		}

		if (mdev_state->s[index].rxtx.head ==
				mdev_state->s[index].rxtx.tail) {
		/*
		 *  Trigger interrupt if tx buffer empty interrupt is
		 *  enabled and fifo is empty
		 */
#if defined(DEBUG_INTR)
			pr_err("Serial port %d: Buffer Empty\n", index);
#endif
			if (mdev_state->s[index].uart_reg[UART_IER] &
							 UART_IER_THRI)
				mtty_trigger_interrupt(mdev_state);
		}
		mutex_unlock(&mdev_state->rxtx_lock);

		break;

	case UART_IER:
		if (mdev_state->s[index].dlab) {
			*buf = (u8)(mdev_state->s[index].divisor >> 8);
			break;
		}
		*buf = mdev_state->s[index].uart_reg[offset] & 0x0f;
		break;

	case UART_IIR:
	{
		u8 ier = mdev_state->s[index].uart_reg[UART_IER];
		*buf = 0;

		mutex_lock(&mdev_state->rxtx_lock);
		/* Interrupt priority 1: Parity, overrun, framing or break */
		if ((ier & UART_IER_RLSI) && mdev_state->s[index].overrun)
			*buf |= UART_IIR_RLSI;

		/* Interrupt priority 2: Fifo trigger level reached */
		if ((ier & UART_IER_RDI) &&
		    (mdev_state->s[index].rxtx.count >=
		      mdev_state->s[index].intr_trigger_level))
			*buf |= UART_IIR_RDI;

		/* Interrupt priotiry 3: transmitter holding register empty */
		if ((ier & UART_IER_THRI) &&
		    (mdev_state->s[index].rxtx.head ==
				mdev_state->s[index].rxtx.tail))
			*buf |= UART_IIR_THRI;

		/* Interrupt priotiry 4: Modem status: CTS, DSR, RI or DCD  */
		if ((ier & UART_IER_MSI) &&
		    (mdev_state->s[index].uart_reg[UART_MCR] &
				 (UART_MCR_RTS | UART_MCR_DTR)))
			*buf |= UART_IIR_MSI;

		/* bit0: 0=> interrupt pending, 1=> no interrupt is pending */
		if (*buf == 0)
			*buf = UART_IIR_NO_INT;

		/* set bit 6 & 7 to be 16550 compatible */
		*buf |= 0xC0;
		mutex_unlock(&mdev_state->rxtx_lock);
	}
	break;

	case UART_LCR:
	case UART_MCR:
		*buf = mdev_state->s[index].uart_reg[offset];
		break;

	case UART_LSR:
	{
		u8 lsr = 0;

		mutex_lock(&mdev_state->rxtx_lock);
		/* atleast one char in FIFO */
		if (mdev_state->s[index].rxtx.head !=
				 mdev_state->s[index].rxtx.tail)
			lsr |= UART_LSR_DR;

		/* if FIFO overrun */
		if (mdev_state->s[index].overrun)
			lsr |= UART_LSR_OE;

		/* transmit FIFO empty and tramsitter empty */
		if (mdev_state->s[index].rxtx.head ==
				 mdev_state->s[index].rxtx.tail)
			lsr |= UART_LSR_TEMT | UART_LSR_THRE;

		mutex_unlock(&mdev_state->rxtx_lock);
		*buf = lsr;
		break;
	}
	case UART_MSR:
		*buf = UART_MSR_DSR | UART_MSR_DDSR | UART_MSR_DCD;

		mutex_lock(&mdev_state->rxtx_lock);
		/* if AFE is 1 and FIFO have space, set CTS bit */
		if (mdev_state->s[index].uart_reg[UART_MCR] &
						 UART_MCR_AFE) {
			if (mdev_state->s[index].rxtx.count <
					mdev_state->s[index].max_fifo_size)
				*buf |= UART_MSR_CTS | UART_MSR_DCTS;
		} else
			*buf |= UART_MSR_CTS | UART_MSR_DCTS;
		mutex_unlock(&mdev_state->rxtx_lock);

		break;

	case UART_SCR:
		*buf = mdev_state->s[index].uart_reg[offset];
		break;

	default:
		break;
	}
}