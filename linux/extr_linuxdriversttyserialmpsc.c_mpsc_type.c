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
struct uart_port {int /*<<< orphan*/  line; } ;

/* Variables and functions */
 char const* MPSC_DRIVER_NAME ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const char *mpsc_type(struct uart_port *port)
{
	pr_debug("mpsc_type[%d]: port type: %s\n", port->line,MPSC_DRIVER_NAME);
	return MPSC_DRIVER_NAME;
}