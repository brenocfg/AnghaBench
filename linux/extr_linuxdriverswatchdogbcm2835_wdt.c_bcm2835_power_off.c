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
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;
struct bcm2835_wdt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bcm2835_restart (struct bcm2835_wdt*,int) ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct bcm2835_wdt* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void bcm2835_power_off(void)
{
	struct device_node *np =
		of_find_compatible_node(NULL, NULL, "brcm,bcm2835-pm-wdt");
	struct platform_device *pdev = of_find_device_by_node(np);
	struct bcm2835_wdt *wdt = platform_get_drvdata(pdev);

	/* Partition 63 tells the firmware that this is a halt */
	__bcm2835_restart(wdt, 63);
}