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
typedef  int u32 ;
struct vme_bridge {struct ca91cx42_driver* driver_priv; } ;
struct ca91cx42_driver {int /*<<< orphan*/  vme_int; scalar_t__ base; int /*<<< orphan*/  iack_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ STATID ; 
 scalar_t__ VINT_EN ; 
 int /*<<< orphan*/  ca91cx42_iack_received (struct ca91cx42_driver*,int) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca91cx42_irq_generate(struct vme_bridge *ca91cx42_bridge, int level,
	int statid)
{
	u32 tmp;
	struct ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	/* Universe can only generate even vectors */
	if (statid & 1)
		return -EINVAL;

	mutex_lock(&bridge->vme_int);

	tmp = ioread32(bridge->base + VINT_EN);

	/* Set Status/ID */
	iowrite32(statid << 24, bridge->base + STATID);

	/* Assert VMEbus IRQ */
	tmp = tmp | (1 << (level + 24));
	iowrite32(tmp, bridge->base + VINT_EN);

	/* Wait for IACK */
	wait_event_interruptible(bridge->iack_queue,
				 ca91cx42_iack_received(bridge, level));

	/* Return interrupt to low state */
	tmp = ioread32(bridge->base + VINT_EN);
	tmp = tmp & ~(1 << (level + 24));
	iowrite32(tmp, bridge->base + VINT_EN);

	mutex_unlock(&bridge->vme_int);

	return 0;
}