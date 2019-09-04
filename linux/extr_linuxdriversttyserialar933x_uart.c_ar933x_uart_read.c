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
struct TYPE_2__ {scalar_t__ membase; } ;
struct ar933x_uart_port {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static inline unsigned int ar933x_uart_read(struct ar933x_uart_port *up,
					    int offset)
{
	return readl(up->port.membase + offset);
}