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
struct pxa8250_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  line; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct pxa8250_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serial8250_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serial_pxa_remove(struct platform_device *pdev)
{
	struct pxa8250_data *data = platform_get_drvdata(pdev);

	serial8250_unregister_port(data->line);

	clk_unprepare(data->clk);

	return 0;
}