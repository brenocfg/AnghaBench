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
typedef  int /*<<< orphan*/  AT91PS_USART ;

/* Variables and functions */
 int /*<<< orphan*/  AT91F_US_PutChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  AT91F_US_TxReady (int /*<<< orphan*/ ) ; 
 scalar_t__ us ; 

int at91_serial_putc(int ch)
{
	if (ch == '\n')
		at91_serial_putc('\r');
	while (!AT91F_US_TxReady((AT91PS_USART)us));
	AT91F_US_PutChar((AT91PS_USART)us, (char)ch);
	return ch;
}