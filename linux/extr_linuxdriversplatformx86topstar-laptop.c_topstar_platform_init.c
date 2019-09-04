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
struct topstar_laptop {int /*<<< orphan*/  platform; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TOPSTAR_LAPTOP_CLASS ; 
 int platform_device_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (int /*<<< orphan*/ ,struct topstar_laptop*) ; 

__attribute__((used)) static int topstar_platform_init(struct topstar_laptop *topstar)
{
	int err;

	topstar->platform = platform_device_alloc(TOPSTAR_LAPTOP_CLASS, -1);
	if (!topstar->platform)
		return -ENOMEM;

	platform_set_drvdata(topstar->platform, topstar);

	err = platform_device_add(topstar->platform);
	if (err)
		goto err_device_put;

	return 0;

err_device_put:
	platform_device_put(topstar->platform);
	return err;
}