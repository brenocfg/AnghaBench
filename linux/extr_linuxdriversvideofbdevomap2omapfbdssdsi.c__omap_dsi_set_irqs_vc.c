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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * isr_table_vc; } ;
struct dsi_data {TYPE_1__ isr_tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_VC_IRQENABLE (int) ; 
 int /*<<< orphan*/  DSI_VC_IRQSTATUS (int) ; 
 int /*<<< orphan*/  DSI_VC_IRQ_ERROR_MASK ; 
 int /*<<< orphan*/  _omap_dsi_configure_irqs (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 

__attribute__((used)) static void _omap_dsi_set_irqs_vc(struct platform_device *dsidev, int vc)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	_omap_dsi_configure_irqs(dsidev, dsi->isr_tables.isr_table_vc[vc],
			ARRAY_SIZE(dsi->isr_tables.isr_table_vc[vc]),
			DSI_VC_IRQ_ERROR_MASK,
			DSI_VC_IRQENABLE(vc), DSI_VC_IRQSTATUS(vc));
}