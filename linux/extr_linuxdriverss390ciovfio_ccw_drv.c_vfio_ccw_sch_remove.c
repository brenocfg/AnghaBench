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
struct vfio_ccw_private {int /*<<< orphan*/  io_region; } ;
struct subchannel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vfio_ccw_private*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_ccw_io_region ; 
 int /*<<< orphan*/  vfio_ccw_mdev_unreg (struct subchannel*) ; 
 int /*<<< orphan*/  vfio_ccw_sch_quiesce (struct subchannel*) ; 

__attribute__((used)) static int vfio_ccw_sch_remove(struct subchannel *sch)
{
	struct vfio_ccw_private *private = dev_get_drvdata(&sch->dev);

	vfio_ccw_sch_quiesce(sch);

	vfio_ccw_mdev_unreg(sch);

	dev_set_drvdata(&sch->dev, NULL);

	kmem_cache_free(vfio_ccw_io_region, private->io_region);
	kfree(private);

	return 0;
}