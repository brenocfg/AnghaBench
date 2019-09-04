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
struct uart_port {int /*<<< orphan*/  type; } ;
struct s3c24xx_uart_info {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int UART_CONFIG_TYPE ; 
 struct s3c24xx_uart_info* s3c24xx_port_to_info (struct uart_port*) ; 
 scalar_t__ s3c24xx_serial_request_port (struct uart_port*) ; 

__attribute__((used)) static void s3c24xx_serial_config_port(struct uart_port *port, int flags)
{
	struct s3c24xx_uart_info *info = s3c24xx_port_to_info(port);

	if (flags & UART_CONFIG_TYPE &&
	    s3c24xx_serial_request_port(port) == 0)
		port->type = info->type;
}