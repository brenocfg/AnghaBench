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
struct uart_amba_port {int /*<<< orphan*/  port; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 struct uart_amba_port* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  amba_reg ; 
 int /*<<< orphan*/  pl011_unregister_port (struct uart_amba_port*) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pl011_remove(struct amba_device *dev)
{
	struct uart_amba_port *uap = amba_get_drvdata(dev);

	uart_remove_one_port(&amba_reg, &uap->port);
	pl011_unregister_port(uap);
	return 0;
}