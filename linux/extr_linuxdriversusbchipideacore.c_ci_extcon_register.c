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
struct ci_hdrc_cable {int /*<<< orphan*/  nb; int /*<<< orphan*/  edev; struct ci_hdrc* ci; } ;
struct ci_hdrc {int /*<<< orphan*/  dev; TYPE_1__* platdata; } ;
struct TYPE_2__ {struct ci_hdrc_cable vbus_extcon; struct ci_hdrc_cable id_extcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_extcon_register_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ci_extcon_register(struct ci_hdrc *ci)
{
	struct ci_hdrc_cable *id, *vbus;
	int ret;

	id = &ci->platdata->id_extcon;
	id->ci = ci;
	if (!IS_ERR_OR_NULL(id->edev)) {
		ret = devm_extcon_register_notifier(ci->dev, id->edev,
						EXTCON_USB_HOST, &id->nb);
		if (ret < 0) {
			dev_err(ci->dev, "register ID failed\n");
			return ret;
		}
	}

	vbus = &ci->platdata->vbus_extcon;
	vbus->ci = ci;
	if (!IS_ERR_OR_NULL(vbus->edev)) {
		ret = devm_extcon_register_notifier(ci->dev, vbus->edev,
						EXTCON_USB, &vbus->nb);
		if (ret < 0) {
			dev_err(ci->dev, "register VBUS failed\n");
			return ret;
		}
	}

	return 0;
}