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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * platform_devices ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 scalar_t__ pnp_registered ; 
 int /*<<< orphan*/  pnp_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mpu401_driver ; 
 int /*<<< orphan*/  snd_mpu401_pnp_driver ; 

__attribute__((used)) static void snd_mpu401_unregister_all(void)
{
	int i;

	if (pnp_registered)
		pnp_unregister_driver(&snd_mpu401_pnp_driver);
	for (i = 0; i < ARRAY_SIZE(platform_devices); ++i)
		platform_device_unregister(platform_devices[i]);
	platform_driver_unregister(&snd_mpu401_driver);
}