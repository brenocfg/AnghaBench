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
struct rndis_wlan_private {int device_type; int param_power_save; int param_power_output; int param_roamtrigger; int param_roamdelta; int param_workaround_interval; void** param_country; int /*<<< orphan*/  param_afterburner; int /*<<< orphan*/  param_frameburst; } ;

/* Variables and functions */
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 int /*<<< orphan*/  modparam_afterburner ; 
 void** modparam_country ; 
 int /*<<< orphan*/  modparam_frameburst ; 
 int modparam_power_output ; 
 int modparam_power_save ; 
 int modparam_roamdelta ; 
 int modparam_roamtrigger ; 
 int modparam_workaround_interval ; 
 int /*<<< orphan*/  strcmp (void**,char*) ; 
 int /*<<< orphan*/  strcpy (void**,char*) ; 
 void* toupper (void*) ; 

__attribute__((used)) static void rndis_copy_module_params(struct usbnet *usbdev, int device_type)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);

	priv->device_type = device_type;

	priv->param_country[0] = modparam_country[0];
	priv->param_country[1] = modparam_country[1];
	priv->param_country[2] = 0;
	priv->param_frameburst   = modparam_frameburst;
	priv->param_afterburner  = modparam_afterburner;
	priv->param_power_save   = modparam_power_save;
	priv->param_power_output = modparam_power_output;
	priv->param_roamtrigger  = modparam_roamtrigger;
	priv->param_roamdelta    = modparam_roamdelta;

	priv->param_country[0] = toupper(priv->param_country[0]);
	priv->param_country[1] = toupper(priv->param_country[1]);
	/* doesn't support EU as country code, use FI instead */
	if (!strcmp(priv->param_country, "EU"))
		strcpy(priv->param_country, "FI");

	if (priv->param_power_save < 0)
		priv->param_power_save = 0;
	else if (priv->param_power_save > 2)
		priv->param_power_save = 2;

	if (priv->param_power_output < 0)
		priv->param_power_output = 0;
	else if (priv->param_power_output > 3)
		priv->param_power_output = 3;

	if (priv->param_roamtrigger < -80)
		priv->param_roamtrigger = -80;
	else if (priv->param_roamtrigger > -60)
		priv->param_roamtrigger = -60;

	if (priv->param_roamdelta < 0)
		priv->param_roamdelta = 0;
	else if (priv->param_roamdelta > 2)
		priv->param_roamdelta = 2;

	if (modparam_workaround_interval < 0)
		priv->param_workaround_interval = 500;
	else
		priv->param_workaround_interval = modparam_workaround_interval;
}