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
struct vme_bridge {struct tsi148_driver* driver_priv; } ;
struct tsi148_driver {int /*<<< orphan*/  vme_int; int /*<<< orphan*/  iack_queue; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_VICR ; 
 int* TSI148_LCSR_VICR_IRQL ; 
 int TSI148_LCSR_VICR_STID_M ; 
 int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi148_iack_received (struct tsi148_driver*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsi148_irq_generate(struct vme_bridge *tsi148_bridge, int level,
	int statid)
{
	u32 tmp;
	struct tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	mutex_lock(&bridge->vme_int);

	/* Read VICR register */
	tmp = ioread32be(bridge->base + TSI148_LCSR_VICR);

	/* Set Status/ID */
	tmp = (tmp & ~TSI148_LCSR_VICR_STID_M) |
		(statid & TSI148_LCSR_VICR_STID_M);
	iowrite32be(tmp, bridge->base + TSI148_LCSR_VICR);

	/* Assert VMEbus IRQ */
	tmp = tmp | TSI148_LCSR_VICR_IRQL[level];
	iowrite32be(tmp, bridge->base + TSI148_LCSR_VICR);

	/* XXX Consider implementing a timeout? */
	wait_event_interruptible(bridge->iack_queue,
		tsi148_iack_received(bridge));

	mutex_unlock(&bridge->vme_int);

	return 0;
}