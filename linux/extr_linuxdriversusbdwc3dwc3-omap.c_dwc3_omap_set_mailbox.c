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
struct dwc3_omap {int /*<<< orphan*/  dev; int /*<<< orphan*/  vbus_reg; } ;
typedef  enum omap_dwc3_vbus_id_status { ____Placeholder_omap_dwc3_vbus_id_status } omap_dwc3_vbus_id_status ;

/* Variables and functions */
#define  OMAP_DWC3_ID_FLOAT 131 
#define  OMAP_DWC3_ID_GROUND 130 
#define  OMAP_DWC3_VBUS_OFF 129 
#define  OMAP_DWC3_VBUS_VALID 128 
 int USBOTGSS_UTMI_OTG_CTRL_IDDIG ; 
 int USBOTGSS_UTMI_OTG_CTRL_SESSEND ; 
 int USBOTGSS_UTMI_OTG_CTRL_SESSVALID ; 
 int USBOTGSS_UTMI_OTG_CTRL_VBUSVALID ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dwc3_omap_read_utmi_ctrl (struct dwc3_omap*) ; 
 int /*<<< orphan*/  dwc3_omap_write_utmi_ctrl (struct dwc3_omap*,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_omap_set_mailbox(struct dwc3_omap *omap,
	enum omap_dwc3_vbus_id_status status)
{
	int	ret;
	u32	val;

	switch (status) {
	case OMAP_DWC3_ID_GROUND:
		if (omap->vbus_reg) {
			ret = regulator_enable(omap->vbus_reg);
			if (ret) {
				dev_err(omap->dev, "regulator enable failed\n");
				return;
			}
		}

		val = dwc3_omap_read_utmi_ctrl(omap);
		val &= ~USBOTGSS_UTMI_OTG_CTRL_IDDIG;
		dwc3_omap_write_utmi_ctrl(omap, val);
		break;

	case OMAP_DWC3_VBUS_VALID:
		val = dwc3_omap_read_utmi_ctrl(omap);
		val &= ~USBOTGSS_UTMI_OTG_CTRL_SESSEND;
		val |= USBOTGSS_UTMI_OTG_CTRL_VBUSVALID
				| USBOTGSS_UTMI_OTG_CTRL_SESSVALID;
		dwc3_omap_write_utmi_ctrl(omap, val);
		break;

	case OMAP_DWC3_ID_FLOAT:
		if (omap->vbus_reg)
			regulator_disable(omap->vbus_reg);
		val = dwc3_omap_read_utmi_ctrl(omap);
		val |= USBOTGSS_UTMI_OTG_CTRL_IDDIG;
		dwc3_omap_write_utmi_ctrl(omap, val);
		break;

	case OMAP_DWC3_VBUS_OFF:
		val = dwc3_omap_read_utmi_ctrl(omap);
		val &= ~(USBOTGSS_UTMI_OTG_CTRL_SESSVALID
				| USBOTGSS_UTMI_OTG_CTRL_VBUSVALID);
		val |= USBOTGSS_UTMI_OTG_CTRL_SESSEND;
		dwc3_omap_write_utmi_ctrl(omap, val);
		break;

	default:
		dev_WARN(omap->dev, "invalid state\n");
	}
}