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
struct uart_port {int dummy; } ;

/* Variables and functions */
 long HV_EOK ; 
 long sun4v_con_putchar (char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void sunhv_console_putchar(struct uart_port *port, char c)
{
	int limit = 1000000;

	while (limit-- > 0) {
		long status = sun4v_con_putchar(c);
		if (status == HV_EOK)
			break;
		udelay(1);
	}
}