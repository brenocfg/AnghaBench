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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct uart_8250_port {int capabilities; TYPE_1__ port; } ;

/* Variables and functions */
 int UART_CAP_RPM ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

void serial8250_rpm_get(struct uart_8250_port *p)
{
	if (!(p->capabilities & UART_CAP_RPM))
		return;
	pm_runtime_get_sync(p->port.dev);
}