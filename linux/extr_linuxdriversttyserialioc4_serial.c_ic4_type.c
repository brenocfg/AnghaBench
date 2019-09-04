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
struct uart_port {scalar_t__ mapbase; } ;

/* Variables and functions */
 scalar_t__ PROTO_RS232 ; 

__attribute__((used)) static const char *ic4_type(struct uart_port *the_port)
{
	if (the_port->mapbase == PROTO_RS232)
		return "SGI IOC4 Serial [rs232]";
	else
		return "SGI IOC4 Serial [rs422]";
}