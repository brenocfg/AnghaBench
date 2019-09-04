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
struct platform_device {int dummy; } ;
struct dsi_data {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  isr_tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  _omap_dsi_set_irqs (struct platform_device*) ; 
 int /*<<< orphan*/  _omap_dsi_set_irqs_cio (struct platform_device*) ; 
 int /*<<< orphan*/  _omap_dsi_set_irqs_vc (struct platform_device*,int) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void _dsi_initialize_irq(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	unsigned long flags;
	int vc;

	spin_lock_irqsave(&dsi->irq_lock, flags);

	memset(&dsi->isr_tables, 0, sizeof(dsi->isr_tables));

	_omap_dsi_set_irqs(dsidev);
	for (vc = 0; vc < 4; ++vc)
		_omap_dsi_set_irqs_vc(dsidev, vc);
	_omap_dsi_set_irqs_cio(dsidev);

	spin_unlock_irqrestore(&dsi->irq_lock, flags);
}