#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_device {TYPE_2__* card; TYPE_1__* ops; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ (* dev_free ) (struct snd_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __snd_device_disconnect (struct snd_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct snd_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct snd_device*) ; 

__attribute__((used)) static void __snd_device_free(struct snd_device *dev)
{
	/* unlink */
	list_del(&dev->list);

	__snd_device_disconnect(dev);
	if (dev->ops->dev_free) {
		if (dev->ops->dev_free(dev))
			dev_err(dev->card->dev, "device free failure\n");
	}
	kfree(dev);
}