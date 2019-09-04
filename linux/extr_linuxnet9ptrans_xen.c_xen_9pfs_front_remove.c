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
struct xen_9pfs_front_priv {int dummy; } ;

/* Variables and functions */
 struct xen_9pfs_front_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_9pfs_front_free (struct xen_9pfs_front_priv*) ; 

__attribute__((used)) static int xen_9pfs_front_remove(struct xenbus_device *dev)
{
	struct xen_9pfs_front_priv *priv = dev_get_drvdata(&dev->dev);

	dev_set_drvdata(&dev->dev, NULL);
	xen_9pfs_front_free(priv);
	return 0;
}