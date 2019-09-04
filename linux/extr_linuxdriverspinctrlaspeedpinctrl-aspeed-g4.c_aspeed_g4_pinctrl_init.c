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

/* Variables and functions */
 int /*<<< orphan*/  aspeed_g4_pinctrl_driver ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aspeed_g4_pinctrl_init(void)
{
	return platform_driver_register(&aspeed_g4_pinctrl_driver);
}