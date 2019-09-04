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
struct lbs_private {struct firmware const* helper_fw; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lbs_fw_loaded (struct lbs_private*,int /*<<< orphan*/ ,struct firmware const*,struct firmware const*) ; 
 int /*<<< orphan*/  load_next_firmware_from_table (struct lbs_private*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static void main_firmware_cb(const struct firmware *firmware, void *context)
{
	struct lbs_private *priv = context;

	if (!firmware) {
		/* Failed to find firmware: try next table entry */
		load_next_firmware_from_table(priv);
		return;
	}

	/* Firmware found! */
	lbs_fw_loaded(priv, 0, priv->helper_fw, firmware);
	if (priv->helper_fw) {
		release_firmware (priv->helper_fw);
		priv->helper_fw = NULL;
	}
	release_firmware (firmware);
}