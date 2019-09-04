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
struct channel_t {int ch_flags; TYPE_1__* ch_cls_uart; } ;
struct TYPE_2__ {int /*<<< orphan*/  isr_fcr; } ;

/* Variables and functions */
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_flush_uart_write(struct channel_t *ch)
{
	if (!ch)
		return;

	writeb((UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_XMIT),
	       &ch->ch_cls_uart->isr_fcr);

	/* Must use *delay family functions in atomic context */
	udelay(10);

	ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
}