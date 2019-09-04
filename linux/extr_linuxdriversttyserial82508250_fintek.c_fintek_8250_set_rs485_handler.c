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
struct TYPE_2__ {int /*<<< orphan*/  rs485_config; struct fintek_8250* private_data; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct fintek_8250 {int pid; } ;

/* Variables and functions */
#define  CHIP_ID_F81216AD 131 
#define  CHIP_ID_F81216H 130 
#define  CHIP_ID_F81865 129 
#define  CHIP_ID_F81866 128 
 int /*<<< orphan*/  fintek_8250_rs485_config ; 

__attribute__((used)) static void fintek_8250_set_rs485_handler(struct uart_8250_port *uart)
{
	struct fintek_8250 *pdata = uart->port.private_data;

	switch (pdata->pid) {
	case CHIP_ID_F81216AD:
	case CHIP_ID_F81216H:
	case CHIP_ID_F81866:
	case CHIP_ID_F81865:
		uart->port.rs485_config = fintek_8250_rs485_config;
		break;

	default: /* No RS485 Auto direction functional */
		break;
	}
}