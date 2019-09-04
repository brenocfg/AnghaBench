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
struct ipw_tty {unsigned int tx_bytes_queued; } ;

/* Variables and functions */

__attribute__((used)) static void ipw_write_packet_sent_callback(void *callback_data,
					   unsigned int packet_length)
{
	struct ipw_tty *tty = callback_data;

	/*
	 * Packet has been sent, so we subtract the number of bytes from our
	 * tally of outstanding TX bytes.
	 */
	tty->tx_bytes_queued -= packet_length;
}