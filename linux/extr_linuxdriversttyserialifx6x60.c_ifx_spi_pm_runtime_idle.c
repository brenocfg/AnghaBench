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
struct spi_device {int dummy; } ;
struct ifx_spi_device {int /*<<< orphan*/  power_status; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_suspend (struct device*) ; 
 struct ifx_spi_device* spi_get_drvdata (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int ifx_spi_pm_runtime_idle(struct device *dev)
{
	struct spi_device *spi = to_spi_device(dev);
	struct ifx_spi_device *ifx_dev = spi_get_drvdata(spi);

	if (!ifx_dev->power_status)
		pm_runtime_suspend(dev);

	return 0;
}