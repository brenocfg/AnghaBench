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

/* Variables and functions */
 int /*<<< orphan*/  st_syscfg_thermal_of_match ; 
 int st_thermal_register (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_syscfg_probe(struct platform_device *pdev)
{
	return st_thermal_register(pdev, st_syscfg_thermal_of_match);
}