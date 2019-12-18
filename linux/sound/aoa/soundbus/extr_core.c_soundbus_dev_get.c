#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct soundbus_dev {TYPE_1__ ofdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* get_device (int /*<<< orphan*/ *) ; 
 struct soundbus_dev* to_soundbus_device (struct device*) ; 

struct soundbus_dev *soundbus_dev_get(struct soundbus_dev *dev)
{
	struct device *tmp;

	if (!dev)
		return NULL;
	tmp = get_device(&dev->ofdev.dev);
	if (tmp)
		return to_soundbus_device(tmp);
	else
		return NULL;
}