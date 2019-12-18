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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_DRIVER ; 
 size_t device_count ; 
 scalar_t__ platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 struct platform_device** platform_devices ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct parport*) ; 

__attribute__((used)) static void snd_portman_attach(struct parport *p)
{
	struct platform_device *device;

	device = platform_device_alloc(PLATFORM_DRIVER, device_count);
	if (!device)
		return;

	/* Temporary assignment to forward the parport */
	platform_set_drvdata(device, p);

	if (platform_device_add(device) < 0) {
		platform_device_put(device);
		return;
	}

	/* Since we dont get the return value of probe
	 * We need to check if device probing succeeded or not */
	if (!platform_get_drvdata(device)) {
		platform_device_unregister(device);
		return;
	}

	/* register device in global table */
	platform_devices[device_count] = device;
	device_count++;
}