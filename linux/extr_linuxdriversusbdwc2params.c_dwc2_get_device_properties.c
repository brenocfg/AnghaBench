#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dwc2_core_params {int oc_disable; int /*<<< orphan*/ * g_tx_fifo_size; int /*<<< orphan*/  g_np_tx_fifo_size; int /*<<< orphan*/  g_rx_fifo_size; } ;
struct dwc2_hsotg {scalar_t__ dr_mode; TYPE_1__* dev; struct dwc2_core_params params; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ USB_DR_MODE_OTG ; 
 scalar_t__ USB_DR_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  device_property_read_u32 (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int device_property_read_u32_array (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 scalar_t__ of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc2_get_device_properties(struct dwc2_hsotg *hsotg)
{
	struct dwc2_core_params *p = &hsotg->params;
	int num;

	if ((hsotg->dr_mode == USB_DR_MODE_PERIPHERAL) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) {
		device_property_read_u32(hsotg->dev, "g-rx-fifo-size",
					 &p->g_rx_fifo_size);

		device_property_read_u32(hsotg->dev, "g-np-tx-fifo-size",
					 &p->g_np_tx_fifo_size);

		num = device_property_read_u32_array(hsotg->dev,
						     "g-tx-fifo-size",
						     NULL, 0);

		if (num > 0) {
			num = min(num, 15);
			memset(p->g_tx_fifo_size, 0,
			       sizeof(p->g_tx_fifo_size));
			device_property_read_u32_array(hsotg->dev,
						       "g-tx-fifo-size",
						       &p->g_tx_fifo_size[1],
						       num);
		}
	}

	if (of_find_property(hsotg->dev->of_node, "disable-over-current", NULL))
		p->oc_disable = true;
}