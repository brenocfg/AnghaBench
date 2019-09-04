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
struct vpfe_device {int /*<<< orphan*/  vpfe_resizer; int /*<<< orphan*/  vpfe_ipipeif; int /*<<< orphan*/  v4l2_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vpfe_ipipeif_ss_buffer_isr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_resizer_dma_isr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t vpfe_imp_dma_isr(int irq, void *dev_id)
{
	struct vpfe_device *vpfe_dev = dev_id;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_imp_dma_isr\n");
	vpfe_ipipeif_ss_buffer_isr(&vpfe_dev->vpfe_ipipeif);
	vpfe_resizer_dma_isr(&vpfe_dev->vpfe_resizer);
	return IRQ_HANDLED;
}