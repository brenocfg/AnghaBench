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
typedef  unsigned char uint ;
struct channel_t {int ch_flags; TYPE_2__* ch_bd; TYPE_1__* ch_cls_uart; } ;
struct TYPE_4__ {int /*<<< orphan*/  helper_tasklet; } ;
struct TYPE_3__ {int /*<<< orphan*/  lsr; } ;

/* Variables and functions */
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 unsigned char UART_LSR_TEMT ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint cls_get_uart_bytes_left(struct channel_t *ch)
{
	unsigned char left = 0;
	unsigned char lsr = 0;

	if (!ch)
		return 0;

	lsr = readb(&ch->ch_cls_uart->lsr);

	/* Determine whether the Transmitter is empty or not */
	if (!(lsr & UART_LSR_TEMT)) {
		if (ch->ch_flags & CH_TX_FIFO_EMPTY)
			tasklet_schedule(&ch->ch_bd->helper_tasklet);
		left = 1;
	} else {
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		left = 0;
	}

	return left;
}