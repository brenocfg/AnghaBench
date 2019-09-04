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
typedef  int uint32_t ;
struct uart_port {int dummy; } ;
struct ioc4_port {int ip_sscr; TYPE_2__* ip_serial_regs; TYPE_1__* ip_uart_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  sscr; int /*<<< orphan*/  shadow; } ;
struct TYPE_3__ {int /*<<< orphan*/  i4u_mcr; } ;

/* Variables and functions */
 int IOC4_SSCR_DMA_EN ; 
 int IOC4_SSCR_DMA_PAUSE ; 
 int IOC4_SSCR_PAUSE_STATE ; 
 int MAXITER ; 
 struct ioc4_port* get_ioc4_port (struct uart_port*,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int set_mcr(struct uart_port *the_port,
		int mask1, int mask2)
{
	struct ioc4_port *port = get_ioc4_port(the_port, 0);
	uint32_t shadow;
	int spiniter = 0;
	char mcr;

	if (!port)
		return -1;

	/* Pause the DMA interface if necessary */
	if (port->ip_sscr & IOC4_SSCR_DMA_EN) {
		writel(port->ip_sscr | IOC4_SSCR_DMA_PAUSE,
			&port->ip_serial_regs->sscr);
		while ((readl(&port->ip_serial_regs->sscr)
					& IOC4_SSCR_PAUSE_STATE) == 0) {
			spiniter++;
			if (spiniter > MAXITER)
				return -1;
		}
	}
	shadow = readl(&port->ip_serial_regs->shadow);
	mcr = (shadow & 0xff000000) >> 24;

	/* Set new value */
	mcr |= mask1;
	shadow |= mask2;

	writeb(mcr, &port->ip_uart_regs->i4u_mcr);
	writel(shadow, &port->ip_serial_regs->shadow);

	/* Re-enable the DMA interface if necessary */
	if (port->ip_sscr & IOC4_SSCR_DMA_EN) {
		writel(port->ip_sscr, &port->ip_serial_regs->sscr);
	}
	return 0;
}