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
typedef  scalar_t__ u32 ;
struct uart_port {scalar_t__ membase; } ;
struct pic32_sport {int dummy; } ;

/* Variables and functions */
 scalar_t__ __raw_readl (scalar_t__) ; 
 struct uart_port* pic32_get_port (struct pic32_sport*) ; 

__attribute__((used)) static inline u32 pic32_uart_readl(struct pic32_sport *sport, u32 reg)
{
	struct uart_port *port = pic32_get_port(sport);

	return	__raw_readl(port->membase + reg);
}