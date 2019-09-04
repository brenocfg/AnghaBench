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
struct siox_master {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct siox_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  siox_master_unregister (struct siox_master*) ; 

__attribute__((used)) static int siox_gpio_remove(struct platform_device *pdev)
{
	struct siox_master *master = platform_get_drvdata(pdev);

	siox_master_unregister(master);

	return 0;
}