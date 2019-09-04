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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * isr_table_vc; } ;
struct dsi_data {int /*<<< orphan*/  irq_lock; TYPE_1__ isr_tables; } ;
typedef  int /*<<< orphan*/  omap_dsi_isr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int _dsi_unregister_isr (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _omap_dsi_set_irqs_vc (struct platform_device*,int) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dsi_unregister_isr_vc(struct platform_device *dsidev, int channel,
		omap_dsi_isr_t isr, void *arg, u32 mask)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	unsigned long flags;
	int r;

	spin_lock_irqsave(&dsi->irq_lock, flags);

	r = _dsi_unregister_isr(isr, arg, mask,
			dsi->isr_tables.isr_table_vc[channel],
			ARRAY_SIZE(dsi->isr_tables.isr_table_vc[channel]));

	if (r == 0)
		_omap_dsi_set_irqs_vc(dsidev, channel);

	spin_unlock_irqrestore(&dsi->irq_lock, flags);

	return r;
}