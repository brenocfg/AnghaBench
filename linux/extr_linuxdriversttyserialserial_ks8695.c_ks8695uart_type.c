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
struct uart_port {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PORT_KS8695 ; 

__attribute__((used)) static const char *ks8695uart_type(struct uart_port *port)
{
	return port->type == PORT_KS8695 ? "KS8695" : NULL;
}