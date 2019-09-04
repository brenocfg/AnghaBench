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
struct usbhs_priv {int dummy; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSF_RUNTIME_PWCTRL ; 
 struct usbhs_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  phy_reset ; 
 int /*<<< orphan*/  usbhs_mod_autonomy_mode (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_platform_call (struct usbhs_priv*,int /*<<< orphan*/ ,struct platform_device*) ; 
 struct platform_device* usbhs_priv_to_pdev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsc_drvcllbck_notify_hotplug (struct platform_device*) ; 
 int /*<<< orphan*/  usbhsc_flags_has (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsc_power_ctrl (struct usbhs_priv*,int) ; 

__attribute__((used)) static int usbhsc_resume(struct device *dev)
{
	struct usbhs_priv *priv = dev_get_drvdata(dev);
	struct platform_device *pdev = usbhs_priv_to_pdev(priv);

	if (!usbhsc_flags_has(priv, USBHSF_RUNTIME_PWCTRL)) {
		usbhsc_power_ctrl(priv, 1);
		usbhs_mod_autonomy_mode(priv);
	}

	usbhs_platform_call(priv, phy_reset, pdev);

	usbhsc_drvcllbck_notify_hotplug(pdev);

	return 0;
}