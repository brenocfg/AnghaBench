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
typedef  int uint8_t ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RNG ; 
 int /*<<< orphan*/  UART_MSR ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DSR ; 
 int UART_MSR_RI ; 
 int siu_read (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int siu_get_mctrl(struct uart_port *port)
{
	uint8_t msr;
	unsigned int mctrl = 0;

	msr = siu_read(port, UART_MSR);
	if (msr & UART_MSR_DCD)
		mctrl |= TIOCM_CAR;
	if (msr & UART_MSR_RI)
		mctrl |= TIOCM_RNG;
	if (msr & UART_MSR_DSR)
		mctrl |= TIOCM_DSR;
	if (msr & UART_MSR_CTS)
		mctrl |= TIOCM_CTS;

	return mctrl;
}