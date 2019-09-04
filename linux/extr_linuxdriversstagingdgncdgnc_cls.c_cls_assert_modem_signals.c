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
struct channel_t {unsigned char ch_mostat; int ch_flags; TYPE_1__* ch_cls_uart; } ;
struct TYPE_2__ {int /*<<< orphan*/  mcr; } ;

/* Variables and functions */
 int CH_LOOPBACK ; 
 unsigned char UART_MCR_LOOP ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_assert_modem_signals(struct channel_t *ch)
{
	unsigned char out;

	if (!ch)
		return;

	out = ch->ch_mostat;

	if (ch->ch_flags & CH_LOOPBACK)
		out |= UART_MCR_LOOP;

	writeb(out, &ch->ch_cls_uart->mcr);

	/* Give time for the UART to actually drop the signals */
	usleep_range(10, 20);
}