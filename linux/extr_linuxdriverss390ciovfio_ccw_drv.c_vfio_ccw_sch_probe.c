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
typedef  int /*<<< orphan*/  u32 ;
struct vfio_ccw_private {int /*<<< orphan*/  io_region; int /*<<< orphan*/  state; int /*<<< orphan*/  avail; int /*<<< orphan*/  io_work; struct subchannel* sch; } ;
struct pmcw {scalar_t__ qf; } ;
struct TYPE_2__ {struct pmcw pmcw; } ;
struct subchannel {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  isc; TYPE_1__ schib; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFIO_CCW_ISC ; 
 int /*<<< orphan*/  VFIO_CCW_STATE_NOT_OPER ; 
 int /*<<< orphan*/  VFIO_CCW_STATE_STANDBY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_disable_subchannel (struct subchannel*) ; 
 int cio_enable_subchannel (struct subchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct vfio_ccw_private*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vfio_ccw_private*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_zalloc (int /*<<< orphan*/ ,int) ; 
 struct vfio_ccw_private* kzalloc (int,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_ccw_io_region ; 
 int vfio_ccw_mdev_reg (struct subchannel*) ; 
 int /*<<< orphan*/  vfio_ccw_sch_io_todo ; 

__attribute__((used)) static int vfio_ccw_sch_probe(struct subchannel *sch)
{
	struct pmcw *pmcw = &sch->schib.pmcw;
	struct vfio_ccw_private *private;
	int ret;

	if (pmcw->qf) {
		dev_warn(&sch->dev, "vfio: ccw: does not support QDIO: %s\n",
			 dev_name(&sch->dev));
		return -ENODEV;
	}

	private = kzalloc(sizeof(*private), GFP_KERNEL | GFP_DMA);
	if (!private)
		return -ENOMEM;

	private->io_region = kmem_cache_zalloc(vfio_ccw_io_region,
					       GFP_KERNEL | GFP_DMA);
	if (!private->io_region) {
		kfree(private);
		return -ENOMEM;
	}

	private->sch = sch;
	dev_set_drvdata(&sch->dev, private);

	spin_lock_irq(sch->lock);
	private->state = VFIO_CCW_STATE_NOT_OPER;
	sch->isc = VFIO_CCW_ISC;
	ret = cio_enable_subchannel(sch, (u32)(unsigned long)sch);
	spin_unlock_irq(sch->lock);
	if (ret)
		goto out_free;

	ret = vfio_ccw_mdev_reg(sch);
	if (ret)
		goto out_disable;

	INIT_WORK(&private->io_work, vfio_ccw_sch_io_todo);
	atomic_set(&private->avail, 1);
	private->state = VFIO_CCW_STATE_STANDBY;

	return 0;

out_disable:
	cio_disable_subchannel(sch);
out_free:
	dev_set_drvdata(&sch->dev, NULL);
	kmem_cache_free(vfio_ccw_io_region, private->io_region);
	kfree(private);
	return ret;
}