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
struct typec_altmode_driver {int (* probe ) (struct typec_altmode*) ;} ;
struct typec_altmode {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;
struct altmode {int /*<<< orphan*/  partner; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int stub1 (struct typec_altmode*) ; 
 struct altmode* to_altmode (struct typec_altmode*) ; 
 struct typec_altmode_driver* to_altmode_driver (int /*<<< orphan*/ ) ; 
 struct typec_altmode* to_typec_altmode (struct device*) ; 
 int typec_altmode_create_links (struct altmode*) ; 
 int /*<<< orphan*/  typec_altmode_remove_links (struct altmode*) ; 

__attribute__((used)) static int typec_probe(struct device *dev)
{
	struct typec_altmode_driver *drv = to_altmode_driver(dev->driver);
	struct typec_altmode *adev = to_typec_altmode(dev);
	struct altmode *altmode = to_altmode(adev);
	int ret;

	/* Fail if the port does not support the alternate mode */
	if (!altmode->partner)
		return -ENODEV;

	ret = typec_altmode_create_links(altmode);
	if (ret) {
		dev_warn(dev, "failed to create symlinks\n");
		return ret;
	}

	ret = drv->probe(adev);
	if (ret)
		typec_altmode_remove_links(altmode);

	return ret;
}