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
typedef  int u32 ;
struct TYPE_2__ {int irq_error_mask; } ;

/* Variables and functions */
 int DISPC_IRQ_GFX_FIFO_UNDERFLOW ; 
 int DISPC_IRQ_OCP_ERR ; 
 int DISPC_IRQ_SYNC_LOST ; 
 int DISPC_IRQ_SYNC_LOST2 ; 
 int DISPC_IRQ_SYNC_LOST3 ; 
 int DISPC_IRQ_SYNC_LOST_DIGIT ; 
 int DISPC_IRQ_VID1_FIFO_UNDERFLOW ; 
 int DISPC_IRQ_VID2_FIFO_UNDERFLOW ; 
 int DISPC_IRQ_VID3_FIFO_UNDERFLOW ; 
 int /*<<< orphan*/  FEAT_MGR_LCD2 ; 
 int /*<<< orphan*/  FEAT_MGR_LCD3 ; 
 TYPE_1__ dispc_compat ; 
 int dss_feat_get_num_ovls () ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void print_irq_status(u32 status)
{
	if ((status & dispc_compat.irq_error_mask) == 0)
		return;

#define PIS(x) (status & DISPC_IRQ_##x) ? (#x " ") : ""

	pr_debug("DISPC IRQ: 0x%x: %s%s%s%s%s%s%s%s%s\n",
		status,
		PIS(OCP_ERR),
		PIS(GFX_FIFO_UNDERFLOW),
		PIS(VID1_FIFO_UNDERFLOW),
		PIS(VID2_FIFO_UNDERFLOW),
		dss_feat_get_num_ovls() > 3 ? PIS(VID3_FIFO_UNDERFLOW) : "",
		PIS(SYNC_LOST),
		PIS(SYNC_LOST_DIGIT),
		dss_has_feature(FEAT_MGR_LCD2) ? PIS(SYNC_LOST2) : "",
		dss_has_feature(FEAT_MGR_LCD3) ? PIS(SYNC_LOST3) : "");
#undef PIS
}