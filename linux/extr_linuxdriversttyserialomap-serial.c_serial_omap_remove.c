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
struct uart_omap_port {int /*<<< orphan*/  pm_qos_request; int /*<<< orphan*/  dev; int /*<<< orphan*/  port; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct uart_omap_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_omap_reg ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int serial_omap_remove(struct platform_device *dev)
{
	struct uart_omap_port *up = platform_get_drvdata(dev);

	pm_runtime_get_sync(up->dev);

	uart_remove_one_port(&serial_omap_reg, &up->port);

	pm_runtime_dont_use_autosuspend(up->dev);
	pm_runtime_put_sync(up->dev);
	pm_runtime_disable(up->dev);
	pm_qos_remove_request(&up->pm_qos_request);
	device_init_wakeup(&dev->dev, false);

	return 0;
}