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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int pxa2xx_spi_remove (struct platform_device*) ; 

__attribute__((used)) static void pxa2xx_spi_shutdown(struct platform_device *pdev)
{
	int status = 0;

	if ((status = pxa2xx_spi_remove(pdev)) != 0)
		dev_err(&pdev->dev, "shutdown failed with %d\n", status);
}