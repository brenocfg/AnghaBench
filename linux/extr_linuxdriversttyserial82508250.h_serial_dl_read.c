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
struct uart_8250_port {int (* dl_read ) (struct uart_8250_port*) ;} ;

/* Variables and functions */
 int stub1 (struct uart_8250_port*) ; 

__attribute__((used)) static inline int serial_dl_read(struct uart_8250_port *up)
{
	return up->dl_read(up);
}