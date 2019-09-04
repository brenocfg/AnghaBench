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
typedef  int tcflag_t ;
struct uart_8250_port {int bugs; int fifo_bug; } ;

/* Variables and functions */
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int PARENB ; 
 int PARODD ; 
 int UART_BUG_PARITY ; 
 unsigned char UART_LCR_EPAR ; 
 unsigned char UART_LCR_PARITY ; 
 unsigned char UART_LCR_STOP ; 
 unsigned char UART_LCR_WLEN5 ; 
 unsigned char UART_LCR_WLEN6 ; 
 unsigned char UART_LCR_WLEN7 ; 
 unsigned char UART_LCR_WLEN8 ; 

__attribute__((used)) static unsigned char serial8250_compute_lcr(struct uart_8250_port *up,
					    tcflag_t c_cflag)
{
	unsigned char cval;

	switch (c_cflag & CSIZE) {
	case CS5:
		cval = UART_LCR_WLEN5;
		break;
	case CS6:
		cval = UART_LCR_WLEN6;
		break;
	case CS7:
		cval = UART_LCR_WLEN7;
		break;
	default:
	case CS8:
		cval = UART_LCR_WLEN8;
		break;
	}

	if (c_cflag & CSTOPB)
		cval |= UART_LCR_STOP;
	if (c_cflag & PARENB) {
		cval |= UART_LCR_PARITY;
		if (up->bugs & UART_BUG_PARITY)
			up->fifo_bug = true;
	}
	if (!(c_cflag & PARODD))
		cval |= UART_LCR_EPAR;
#ifdef CMSPAR
	if (c_cflag & CMSPAR)
		cval |= UART_LCR_SPAR;
#endif

	return cval;
}