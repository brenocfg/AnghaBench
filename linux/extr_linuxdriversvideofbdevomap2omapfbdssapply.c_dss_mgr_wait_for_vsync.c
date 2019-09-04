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
struct omap_overlay_manager {int /*<<< orphan*/  id; TYPE_1__* output; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_IRQ_EVSYNC_EVEN ; 
 int /*<<< orphan*/  DISPC_IRQ_EVSYNC_ODD ; 
 int ENODEV ; 
#define  OMAP_DSS_OUTPUT_HDMI 129 
#define  OMAP_DSS_OUTPUT_VENC 128 
 int /*<<< orphan*/  dispc_mgr_get_vsync_irq (int /*<<< orphan*/ ) ; 
 int dispc_runtime_get () ; 
 int /*<<< orphan*/  dispc_runtime_put () ; 
 unsigned long msecs_to_jiffies (int) ; 
 int omap_dispc_wait_for_irq_interruptible_timeout (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int dss_mgr_wait_for_vsync(struct omap_overlay_manager *mgr)
{
	unsigned long timeout = msecs_to_jiffies(500);
	u32 irq;
	int r;

	if (mgr->output == NULL)
		return -ENODEV;

	r = dispc_runtime_get();
	if (r)
		return r;

	switch (mgr->output->id) {
	case OMAP_DSS_OUTPUT_VENC:
		irq = DISPC_IRQ_EVSYNC_ODD;
		break;
	case OMAP_DSS_OUTPUT_HDMI:
		irq = DISPC_IRQ_EVSYNC_EVEN;
		break;
	default:
		irq = dispc_mgr_get_vsync_irq(mgr->id);
		break;
	}

	r = omap_dispc_wait_for_irq_interruptible_timeout(irq, timeout);

	dispc_runtime_put();

	return r;
}