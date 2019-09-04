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
struct jsm_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cls_flush_uart_read(struct jsm_channel *ch)
{
	if (!ch)
		return;

	/*
	 * For complete POSIX compatibility, we should be purging the
	 * read FIFO in the UART here.
	 *
	 * However, clearing the read FIFO (UART_FCR_CLEAR_RCVR) also
	 * incorrectly flushes write data as well as just basically trashing the
	 * FIFO.
	 *
	 * Presumably, this is a bug in this UART.
	 */

	udelay(10);
}