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
struct pnx8xxx_port {int /*<<< orphan*/  port; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct pnx8xxx_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pnx8xxx_reg ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pnx8xxx_serial_remove(struct platform_device *pdev)
{
	struct pnx8xxx_port *sport = platform_get_drvdata(pdev);

	if (sport)
		uart_remove_one_port(&pnx8xxx_reg, &sport->port);

	return 0;
}