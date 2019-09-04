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
struct siox_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct siox_device*) ; 
 struct siox_device* to_siox_device (struct device*) ; 

__attribute__((used)) static void siox_device_release(struct device *dev)
{
	struct siox_device *sdevice = to_siox_device(dev);

	kfree(sdevice);
}