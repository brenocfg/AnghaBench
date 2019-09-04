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
struct usbhs_mod {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSF_RUNTIME_PWCTRL ; 
 struct usbhs_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stop ; 
 int /*<<< orphan*/  usbhs_mod_call (struct usbhs_priv*,int /*<<< orphan*/ ,struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_mod_change (struct usbhs_priv*,int) ; 
 struct usbhs_mod* usbhs_mod_get_current (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsc_flags_has (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsc_power_ctrl (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsc_suspend(struct device *dev)
{
	struct usbhs_priv *priv = dev_get_drvdata(dev);
	struct usbhs_mod *mod = usbhs_mod_get_current(priv);

	if (mod) {
		usbhs_mod_call(priv, stop, priv);
		usbhs_mod_change(priv, -1);
	}

	if (mod || !usbhsc_flags_has(priv, USBHSF_RUNTIME_PWCTRL))
		usbhsc_power_ctrl(priv, 0);

	return 0;
}