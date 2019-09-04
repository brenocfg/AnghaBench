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
struct wiphy {int dummy; } ;
struct wil6210_priv {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum wmi_ps_profile_type { ____Placeholder_wmi_ps_profile_type } wmi_ps_profile_type ;

/* Variables and functions */
 int WMI_PS_PROFILE_TYPE_DEFAULT ; 
 int WMI_PS_PROFILE_TYPE_PS_DISABLED ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int,int) ; 
 int wil_ps_update (struct wil6210_priv*,int) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static int wil_cfg80211_set_power_mgmt(struct wiphy *wiphy,
				       struct net_device *dev,
				       bool enabled, int timeout)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	enum wmi_ps_profile_type ps_profile;

	wil_dbg_misc(wil, "enabled=%d, timeout=%d\n",
		     enabled, timeout);

	if (enabled)
		ps_profile = WMI_PS_PROFILE_TYPE_DEFAULT;
	else
		ps_profile = WMI_PS_PROFILE_TYPE_PS_DISABLED;

	return wil_ps_update(wil, ps_profile);
}