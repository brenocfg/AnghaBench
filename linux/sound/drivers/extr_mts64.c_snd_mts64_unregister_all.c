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
 int SNDRV_CARDS ; 
 int /*<<< orphan*/  mts64_parport_driver ; 
 int /*<<< orphan*/  parport_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** platform_devices ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mts64_driver ; 

__attribute__((used)) static void snd_mts64_unregister_all(void)
{
	int i;

	for (i = 0; i < SNDRV_CARDS; ++i) {
		if (platform_devices[i]) {
			platform_device_unregister(platform_devices[i]);
			platform_devices[i] = NULL;
		}
	}		
	platform_driver_unregister(&snd_mts64_driver);
	parport_unregister_driver(&mts64_parport_driver);
}