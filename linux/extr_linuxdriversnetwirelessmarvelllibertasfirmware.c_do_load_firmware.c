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
struct lbs_private {int /*<<< orphan*/  fw_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  lbs_deb_fw (char*,...) ; 
 int /*<<< orphan*/  lbs_fw_loaded (struct lbs_private*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lbs_private*,void (*) (struct firmware const*,void*)) ; 

__attribute__((used)) static void do_load_firmware(struct lbs_private *priv, const char *name,
	void (*cb)(const struct firmware *fw, void *context))
{
	int ret;

	lbs_deb_fw("Requesting %s\n", name);
	ret = request_firmware_nowait(THIS_MODULE, true, name,
			priv->fw_device, GFP_KERNEL, priv, cb);
	if (ret) {
		lbs_deb_fw("request_firmware_nowait error %d\n", ret);
		lbs_fw_loaded(priv, ret, NULL, NULL);
	}
}