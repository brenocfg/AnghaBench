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
typedef  int /*<<< orphan*/  u8 ;
struct vnt_private {int firmware_version; TYPE_1__* usb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FIRMWARE_VERSION ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_VERSION ; 
 int /*<<< orphan*/  MESSAGE_TYPE_READ ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int vnt_control_in (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_firmware_branch_to_sram (struct vnt_private*) ; 

int vnt_check_firmware_version(struct vnt_private *priv)
{
	int status;

	status = vnt_control_in(priv,
				MESSAGE_TYPE_READ,
				0,
				MESSAGE_REQUEST_VERSION,
				2,
				(u8 *)&priv->firmware_version);

	dev_dbg(&priv->usb->dev, "Firmware Version [%04x]\n",
		priv->firmware_version);

	if (status != STATUS_SUCCESS) {
		dev_dbg(&priv->usb->dev, "Firmware Invalid.\n");
		return false;
	}
	if (priv->firmware_version == 0xFFFF) {
		dev_dbg(&priv->usb->dev, "In Loader.\n");
		return false;
	}

	dev_dbg(&priv->usb->dev, "Firmware Version [%04x]\n",
		priv->firmware_version);

	if (priv->firmware_version < FIRMWARE_VERSION) {
		/* branch to loader for download new firmware */
		vnt_firmware_branch_to_sram(priv);
		return false;
	}
	return true;
}