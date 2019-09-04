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
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct vscsibk_info {scalar_t__ irq; } ;

/* Variables and functions */
 struct vscsibk_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsiback_disconnect (struct vscsibk_info*) ; 
 int /*<<< orphan*/  scsiback_release_translation_entry (struct vscsibk_info*) ; 

__attribute__((used)) static int scsiback_remove(struct xenbus_device *dev)
{
	struct vscsibk_info *info = dev_get_drvdata(&dev->dev);

	if (info->irq)
		scsiback_disconnect(info);

	scsiback_release_translation_entry(info);

	dev_set_drvdata(&dev->dev, NULL);

	return 0;
}