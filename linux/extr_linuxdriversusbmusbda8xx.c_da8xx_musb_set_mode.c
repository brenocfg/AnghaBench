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
typedef  int u8 ;
struct musb {int /*<<< orphan*/  is_initialized; TYPE_1__* controller; } ;
struct da8xx_glue {int /*<<< orphan*/  phy; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MUSB_HOST 130 
#define  MUSB_OTG 129 
#define  MUSB_PERIPHERAL 128 
 int PHY_MODE_USB_DEVICE ; 
 int PHY_MODE_USB_HOST ; 
 int PHY_MODE_USB_OTG ; 
 struct da8xx_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int phy_set_mode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da8xx_musb_set_mode(struct musb *musb, u8 musb_mode)
{
	struct da8xx_glue *glue = dev_get_drvdata(musb->controller->parent);
	enum phy_mode phy_mode;

	/*
	 * The PHY has some issues when it is forced in device or host mode.
	 * Unless the user request another mode, configure the PHY in OTG mode.
	 */
	if (!musb->is_initialized)
		return phy_set_mode(glue->phy, PHY_MODE_USB_OTG);

	switch (musb_mode) {
	case MUSB_HOST:		/* Force VBUS valid, ID = 0 */
		phy_mode = PHY_MODE_USB_HOST;
		break;
	case MUSB_PERIPHERAL:	/* Force VBUS valid, ID = 1 */
		phy_mode = PHY_MODE_USB_DEVICE;
		break;
	case MUSB_OTG:		/* Don't override the VBUS/ID comparators */
		phy_mode = PHY_MODE_USB_OTG;
		break;
	default:
		return -EINVAL;
	}

	return phy_set_mode(glue->phy, phy_mode);
}