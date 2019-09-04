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
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sxgbe_platform_driver ; 

int sxgbe_register_platform(void)
{
	int err;

	err = platform_driver_register(&sxgbe_platform_driver);
	if (err)
		pr_err("failed to register the platform driver\n");

	return err;
}