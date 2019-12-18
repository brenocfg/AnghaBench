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
struct snd_hwdep {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* private_free ) (struct snd_hwdep*) ;} ;
struct snd_device {struct snd_hwdep* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_hwdep*) ; 

__attribute__((used)) static int snd_hwdep_dev_free(struct snd_device *device)
{
	struct snd_hwdep *hwdep = device->device_data;
	if (!hwdep)
		return 0;
	if (hwdep->private_free)
		hwdep->private_free(hwdep);
	put_device(&hwdep->dev);
	return 0;
}