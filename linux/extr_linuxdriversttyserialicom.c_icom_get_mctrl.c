#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dram; } ;
struct TYPE_4__ {int /*<<< orphan*/  isr; } ;

/* Variables and functions */
 unsigned char ICOM_CTS ; 
 unsigned char ICOM_DCD ; 
 unsigned char ICOM_DSR ; 
 TYPE_2__* ICOM_PORT ; 
 unsigned char ICOM_RI ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RNG ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int icom_get_mctrl(struct uart_port *port)
{
	unsigned char status;
	unsigned int result;

	trace(ICOM_PORT, "GET_MODEM", 0);

	status = readb(&ICOM_PORT->dram->isr);

	result = ((status & ICOM_DCD) ? TIOCM_CAR : 0)
	    | ((status & ICOM_RI) ? TIOCM_RNG : 0)
	    | ((status & ICOM_DSR) ? TIOCM_DSR : 0)
	    | ((status & ICOM_CTS) ? TIOCM_CTS : 0);
	return result;
}