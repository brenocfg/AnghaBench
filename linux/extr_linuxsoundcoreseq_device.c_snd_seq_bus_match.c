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
struct snd_seq_driver {scalar_t__ argsize; int /*<<< orphan*/  id; } ;
struct snd_seq_device {scalar_t__ argsize; int /*<<< orphan*/  id; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_seq_device* to_seq_dev (struct device*) ; 
 struct snd_seq_driver* to_seq_drv (struct device_driver*) ; 

__attribute__((used)) static int snd_seq_bus_match(struct device *dev, struct device_driver *drv)
{
	struct snd_seq_device *sdev = to_seq_dev(dev);
	struct snd_seq_driver *sdrv = to_seq_drv(drv);

	return strcmp(sdrv->id, sdev->id) == 0 &&
		sdrv->argsize == sdev->argsize;
}