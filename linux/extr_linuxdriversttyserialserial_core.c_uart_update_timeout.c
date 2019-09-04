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
struct uart_port {unsigned int fifosize; unsigned int timeout; } ;

/* Variables and functions */
#define  CS5 130 
#define  CS6 129 
#define  CS7 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 unsigned int HZ ; 
 unsigned int PARENB ; 

void
uart_update_timeout(struct uart_port *port, unsigned int cflag,
		    unsigned int baud)
{
	unsigned int bits;

	/* byte size and parity */
	switch (cflag & CSIZE) {
	case CS5:
		bits = 7;
		break;
	case CS6:
		bits = 8;
		break;
	case CS7:
		bits = 9;
		break;
	default:
		bits = 10;
		break; /* CS8 */
	}

	if (cflag & CSTOPB)
		bits++;
	if (cflag & PARENB)
		bits++;

	/*
	 * The total number of bits to be transmitted in the fifo.
	 */
	bits = bits * port->fifosize;

	/*
	 * Figure the timeout to send the above number of bits.
	 * Add .02 seconds of slop
	 */
	port->timeout = (HZ * bits) / baud + HZ/50;
}