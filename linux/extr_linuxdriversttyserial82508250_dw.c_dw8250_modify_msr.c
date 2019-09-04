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
struct uart_port {struct dw8250_data* private_data; } ;
struct dw8250_data {int msr_mask_on; int msr_mask_off; } ;

/* Variables and functions */
 int UART_MSR ; 

__attribute__((used)) static inline int dw8250_modify_msr(struct uart_port *p, int offset, int value)
{
	struct dw8250_data *d = p->private_data;

	/* Override any modem control signals if needed */
	if (offset == UART_MSR) {
		value |= d->msr_mask_on;
		value &= ~d->msr_mask_off;
	}

	return value;
}