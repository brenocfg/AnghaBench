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
struct TYPE_2__ {size_t type; } ;
struct uart_8250_port {int /*<<< orphan*/  fcr; TYPE_1__ port; } ;
struct serial8250_config {unsigned char* rxtrig_bytes; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t UART_FCR_R_TRIG_BITS (int /*<<< orphan*/ ) ; 
 struct serial8250_config* uart_config ; 

__attribute__((used)) static int fcr_get_rxtrig_bytes(struct uart_8250_port *up)
{
	const struct serial8250_config *conf_type = &uart_config[up->port.type];
	unsigned char bytes;

	bytes = conf_type->rxtrig_bytes[UART_FCR_R_TRIG_BITS(up->fcr)];

	return bytes ? bytes : -EOPNOTSUPP;
}