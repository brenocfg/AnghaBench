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
struct xenbus_device_id {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct xen_snd_front_info {struct xenbus_device* xb_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XenbusStateInitialising ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct xen_snd_front_info*) ; 
 struct xen_snd_front_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xen_drv_probe(struct xenbus_device *xb_dev,
			 const struct xenbus_device_id *id)
{
	struct xen_snd_front_info *front_info;

	front_info = devm_kzalloc(&xb_dev->dev,
				  sizeof(*front_info), GFP_KERNEL);
	if (!front_info)
		return -ENOMEM;

	front_info->xb_dev = xb_dev;
	dev_set_drvdata(&xb_dev->dev, front_info);

	return xenbus_switch_state(xb_dev, XenbusStateInitialising);
}