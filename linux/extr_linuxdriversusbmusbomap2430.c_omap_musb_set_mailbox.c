#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_musb_board_data {int /*<<< orphan*/  interface_type; } ;
struct omap2430_glue {int status; int /*<<< orphan*/  control_otghs; } ;
struct musb_hdrc_platform_data {struct omap_musb_board_data* board_data; } ;
struct musb {TYPE_1__* xceiv; int /*<<< orphan*/  controller; int /*<<< orphan*/  gadget_driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  last_event; int /*<<< orphan*/  notifier; TYPE_2__* otg; } ;

/* Variables and functions */
#define  MUSB_ID_FLOAT 131 
#define  MUSB_ID_GROUND 130 
 int /*<<< orphan*/  MUSB_INTERFACE_UTMI ; 
#define  MUSB_VBUS_OFF 129 
#define  MUSB_VBUS_VALID 128 
 int /*<<< orphan*/  OTG_STATE_A_IDLE ; 
 int /*<<< orphan*/  OTG_STATE_B_IDLE ; 
 int /*<<< orphan*/  USB_EVENT_ID ; 
 int /*<<< orphan*/  USB_EVENT_NONE ; 
 int /*<<< orphan*/  USB_EVENT_VBUS ; 
 int /*<<< orphan*/  USB_MODE_DEVICE ; 
 int /*<<< orphan*/  USB_MODE_DISCONNECT ; 
 int /*<<< orphan*/  USB_MODE_HOST ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct musb_hdrc_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct musb* glue_to_musb (struct omap2430_glue*) ; 
 int /*<<< orphan*/  omap2430_musb_set_vbus (struct musb*,int) ; 
 int /*<<< orphan*/  omap_control_usb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_set_vbus (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_musb_set_mailbox(struct omap2430_glue *glue)
{
	struct musb *musb = glue_to_musb(glue);
	struct musb_hdrc_platform_data *pdata =
		dev_get_platdata(musb->controller);
	struct omap_musb_board_data *data = pdata->board_data;

	pm_runtime_get_sync(musb->controller);
	switch (glue->status) {
	case MUSB_ID_GROUND:
		dev_dbg(musb->controller, "ID GND\n");

		musb->xceiv->otg->state = OTG_STATE_A_IDLE;
		musb->xceiv->last_event = USB_EVENT_ID;
		if (musb->gadget_driver) {
			omap_control_usb_set_mode(glue->control_otghs,
				USB_MODE_HOST);
			omap2430_musb_set_vbus(musb, 1);
		}
		break;

	case MUSB_VBUS_VALID:
		dev_dbg(musb->controller, "VBUS Connect\n");

		musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		musb->xceiv->last_event = USB_EVENT_VBUS;
		omap_control_usb_set_mode(glue->control_otghs, USB_MODE_DEVICE);
		break;

	case MUSB_ID_FLOAT:
	case MUSB_VBUS_OFF:
		dev_dbg(musb->controller, "VBUS Disconnect\n");

		musb->xceiv->last_event = USB_EVENT_NONE;
		if (musb->gadget_driver)
			omap2430_musb_set_vbus(musb, 0);

		if (data->interface_type == MUSB_INTERFACE_UTMI)
			otg_set_vbus(musb->xceiv->otg, 0);

		omap_control_usb_set_mode(glue->control_otghs,
			USB_MODE_DISCONNECT);
		break;
	default:
		dev_dbg(musb->controller, "ID float\n");
	}
	pm_runtime_mark_last_busy(musb->controller);
	pm_runtime_put_autosuspend(musb->controller);
	atomic_notifier_call_chain(&musb->xceiv->notifier,
			musb->xceiv->last_event, NULL);
}