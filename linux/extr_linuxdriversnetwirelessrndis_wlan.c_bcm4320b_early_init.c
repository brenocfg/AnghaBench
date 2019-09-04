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
struct usbnet {int dummy; } ;
struct rndis_wlan_private {char* param_country; int param_power_save; int param_power_output; int param_roamtrigger; int param_roamdelta; scalar_t__ param_afterburner; scalar_t__ param_frameburst; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_BCM4320B ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 int /*<<< orphan*/  rndis_copy_module_params (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndis_set_config_parameter_str (struct usbnet*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int bcm4320b_early_init(struct usbnet *usbdev)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);
	char buf[8];

	rndis_copy_module_params(usbdev, RNDIS_BCM4320B);

	/* Early initialization settings, setting these won't have effect
	 * if called after generic_rndis_bind().
	 */

	rndis_set_config_parameter_str(usbdev, "Country", priv->param_country);
	rndis_set_config_parameter_str(usbdev, "FrameBursting",
					priv->param_frameburst ? "1" : "0");
	rndis_set_config_parameter_str(usbdev, "Afterburner",
					priv->param_afterburner ? "1" : "0");
	sprintf(buf, "%d", priv->param_power_save);
	rndis_set_config_parameter_str(usbdev, "PowerSaveMode", buf);
	sprintf(buf, "%d", priv->param_power_output);
	rndis_set_config_parameter_str(usbdev, "PwrOut", buf);
	sprintf(buf, "%d", priv->param_roamtrigger);
	rndis_set_config_parameter_str(usbdev, "RoamTrigger", buf);
	sprintf(buf, "%d", priv->param_roamdelta);
	rndis_set_config_parameter_str(usbdev, "RoamDelta", buf);

	return 0;
}