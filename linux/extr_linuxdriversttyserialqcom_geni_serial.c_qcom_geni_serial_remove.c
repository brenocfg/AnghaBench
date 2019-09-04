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
struct uart_driver {int dummy; } ;
struct TYPE_2__ {struct uart_driver* private_data; } ;
struct qcom_geni_serial_port {TYPE_1__ uport; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct qcom_geni_serial_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  uart_remove_one_port (struct uart_driver*,TYPE_1__*) ; 

__attribute__((used)) static int qcom_geni_serial_remove(struct platform_device *pdev)
{
	struct qcom_geni_serial_port *port = platform_get_drvdata(pdev);
	struct uart_driver *drv = port->uport.private_data;

	uart_remove_one_port(drv, &port->uport);
	return 0;
}