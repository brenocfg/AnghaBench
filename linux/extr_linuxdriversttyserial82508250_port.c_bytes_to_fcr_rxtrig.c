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
struct uart_8250_port {TYPE_1__ port; } ;
struct serial8250_config {unsigned char* rxtrig_bytes; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  UART_FCR_R_TRIG_00 ; 
 int UART_FCR_R_TRIG_11 ; 
 size_t UART_FCR_R_TRIG_BITS (int /*<<< orphan*/ ) ; 
 int UART_FCR_R_TRIG_MAX_STATE ; 
 int UART_FCR_R_TRIG_SHIFT ; 
 struct serial8250_config* uart_config ; 

__attribute__((used)) static int bytes_to_fcr_rxtrig(struct uart_8250_port *up, unsigned char bytes)
{
	const struct serial8250_config *conf_type = &uart_config[up->port.type];
	int i;

	if (!conf_type->rxtrig_bytes[UART_FCR_R_TRIG_BITS(UART_FCR_R_TRIG_00)])
		return -EOPNOTSUPP;

	for (i = 1; i < UART_FCR_R_TRIG_MAX_STATE; i++) {
		if (bytes < conf_type->rxtrig_bytes[i])
			/* Use the nearest lower value */
			return (--i) << UART_FCR_R_TRIG_SHIFT;
	}

	return UART_FCR_R_TRIG_11;
}