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
struct pcmcia_socket {int /*<<< orphan*/ * resource_ops; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct class_interface {int dummy; } ;

/* Variables and functions */
 struct pcmcia_socket* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pccard_nonstatic_ops ; 
 int /*<<< orphan*/  rsrc_attributes ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pccard_sysfs_remove_rsrc(struct device *dev,
					       struct class_interface *class_intf)
{
	struct pcmcia_socket *s = dev_get_drvdata(dev);

	if (s->resource_ops != &pccard_nonstatic_ops)
		return;
	sysfs_remove_group(&dev->kobj, &rsrc_attributes);
}