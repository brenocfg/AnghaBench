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
struct renesas_usbhs_driver_callback {int /*<<< orphan*/ * notify_hotplug; } ;
struct renesas_usbhs_platform_info {struct renesas_usbhs_driver_callback driver_callback; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSF_RUNTIME_PWCTRL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hardware_exit ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct renesas_usbhs_platform_info* renesas_usbhs_get_info (struct platform_device*) ; 
 int /*<<< orphan*/  usbhs_fifo_remove (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_mod_remove (struct usbhs_priv*) ; 
 struct usbhs_priv* usbhs_pdev_to_priv (struct platform_device*) ; 
 int /*<<< orphan*/  usbhs_pipe_remove (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_platform_call (struct usbhs_priv*,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  usbhsc_flags_has (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsc_power_ctrl (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhs_remove(struct platform_device *pdev)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	struct renesas_usbhs_platform_info *info = renesas_usbhs_get_info(pdev);
	struct renesas_usbhs_driver_callback *dfunc = &info->driver_callback;

	dev_dbg(&pdev->dev, "usb remove\n");

	dfunc->notify_hotplug = NULL;

	/* power off */
	if (!usbhsc_flags_has(priv, USBHSF_RUNTIME_PWCTRL))
		usbhsc_power_ctrl(priv, 0);

	pm_runtime_disable(&pdev->dev);

	usbhs_platform_call(priv, hardware_exit, pdev);
	usbhs_mod_remove(priv);
	usbhs_fifo_remove(priv);
	usbhs_pipe_remove(priv);

	return 0;
}