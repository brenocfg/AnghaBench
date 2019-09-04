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
struct TYPE_2__ {scalar_t__ type; } ;
struct uart_8250_port {int capabilities; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ PORT_XR17D15X ; 
 scalar_t__ PORT_XR17V35X ; 
 int UART_CAP_EFR ; 
 int UART_CAP_SLEEP ; 
 int /*<<< orphan*/  UART_EFR ; 
 unsigned char UART_EFR_ECB ; 
 int /*<<< orphan*/  UART_EXAR_SLEEP ; 
 int /*<<< orphan*/  UART_IER ; 
 unsigned char UART_IERX_SLEEP ; 
 int /*<<< orphan*/  UART_LCR ; 
 unsigned char UART_LCR_CONF_MODE_B ; 
 int /*<<< orphan*/  serial8250_rpm_get (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_put (struct uart_8250_port*) ; 
 unsigned char serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void serial8250_set_sleep(struct uart_8250_port *p, int sleep)
{
	unsigned char lcr = 0, efr = 0;
	/*
	 * Exar UARTs have a SLEEP register that enables or disables
	 * each UART to enter sleep mode separately.  On the XR17V35x the
	 * register is accessible to each UART at the UART_EXAR_SLEEP
	 * offset but the UART channel may only write to the corresponding
	 * bit.
	 */
	serial8250_rpm_get(p);
	if ((p->port.type == PORT_XR17V35X) ||
	   (p->port.type == PORT_XR17D15X)) {
		serial_out(p, UART_EXAR_SLEEP, sleep ? 0xff : 0);
		goto out;
	}

	if (p->capabilities & UART_CAP_SLEEP) {
		if (p->capabilities & UART_CAP_EFR) {
			lcr = serial_in(p, UART_LCR);
			efr = serial_in(p, UART_EFR);
			serial_out(p, UART_LCR, UART_LCR_CONF_MODE_B);
			serial_out(p, UART_EFR, UART_EFR_ECB);
			serial_out(p, UART_LCR, 0);
		}
		serial_out(p, UART_IER, sleep ? UART_IERX_SLEEP : 0);
		if (p->capabilities & UART_CAP_EFR) {
			serial_out(p, UART_LCR, UART_LCR_CONF_MODE_B);
			serial_out(p, UART_EFR, efr);
			serial_out(p, UART_LCR, lcr);
		}
	}
out:
	serial8250_rpm_put(p);
}