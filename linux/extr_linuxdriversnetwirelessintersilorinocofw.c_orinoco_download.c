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
struct orinoco_private {int firmware_type; } ;

/* Variables and functions */
#define  FIRMWARE_TYPE_AGERE 130 
#define  FIRMWARE_TYPE_INTERSIL 129 
#define  FIRMWARE_TYPE_SYMBOL 128 
 int orinoco_dl_firmware (struct orinoco_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * orinoco_fw ; 
 int symbol_dl_firmware (struct orinoco_private*,int /*<<< orphan*/ *) ; 

int orinoco_download(struct orinoco_private *priv)
{
	int err = 0;
	/* Reload firmware */
	switch (priv->firmware_type) {
	case FIRMWARE_TYPE_AGERE:
		/* case FIRMWARE_TYPE_INTERSIL: */
		err = orinoco_dl_firmware(priv,
					  &orinoco_fw[priv->firmware_type], 0);
		break;

	case FIRMWARE_TYPE_SYMBOL:
		err = symbol_dl_firmware(priv,
					 &orinoco_fw[priv->firmware_type]);
		break;
	case FIRMWARE_TYPE_INTERSIL:
		break;
	}
	/* TODO: if we fail we probably need to reinitialise
	 * the driver */

	return err;
}