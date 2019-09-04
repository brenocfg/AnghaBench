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
struct jsm_channel {int ch_flags; TYPE_1__* ch_bd; TYPE_2__* ch_cls_uart; } ;
struct TYPE_4__ {int /*<<< orphan*/  isr_fcr; } ;
struct TYPE_3__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int /*<<< orphan*/  IOCTL ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_flush_uart_write(struct jsm_channel *ch)
{
	u8 tmp = 0;
	u8 i = 0;

	if (!ch)
		return;

	writeb((UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_XMIT),
						&ch->ch_cls_uart->isr_fcr);

	for (i = 0; i < 10; i++) {
		/* Check to see if the UART feels it completely flushed FIFO */
		tmp = readb(&ch->ch_cls_uart->isr_fcr);
		if (tmp & UART_FCR_CLEAR_XMIT) {
			jsm_dbg(IOCTL, &ch->ch_bd->pci_dev,
				"Still flushing TX UART... i: %d\n", i);
			udelay(10);
		} else
			break;
	}

	ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
}