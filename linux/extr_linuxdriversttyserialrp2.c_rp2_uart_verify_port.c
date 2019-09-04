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
struct serial_struct {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PORT_RP2 ; 
 scalar_t__ PORT_UNKNOWN ; 

__attribute__((used)) static int rp2_uart_verify_port(struct uart_port *port,
				   struct serial_struct *ser)
{
	if (ser->type != PORT_UNKNOWN && ser->type != PORT_RP2)
		return -EINVAL;

	return 0;
}