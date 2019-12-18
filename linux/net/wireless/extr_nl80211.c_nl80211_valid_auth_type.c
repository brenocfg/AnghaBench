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
struct TYPE_2__ {int features; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;
typedef  enum nl80211_commands { ____Placeholder_nl80211_commands } nl80211_commands ;
typedef  enum nl80211_auth_type { ____Placeholder_nl80211_auth_type } nl80211_auth_type ;

/* Variables and functions */
 int NL80211_AUTHTYPE_FILS_PK ; 
 int NL80211_AUTHTYPE_FILS_SK ; 
 int NL80211_AUTHTYPE_FILS_SK_PFS ; 
 int NL80211_AUTHTYPE_MAX ; 
 int NL80211_AUTHTYPE_SAE ; 
#define  NL80211_CMD_AUTHENTICATE 130 
#define  NL80211_CMD_CONNECT 129 
#define  NL80211_CMD_START_AP 128 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_FILS_SK_OFFLOAD ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_FILS_STA ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_SAE_OFFLOAD ; 
 int NL80211_FEATURE_SAE ; 
 int /*<<< orphan*/  wiphy_ext_feature_isset (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nl80211_valid_auth_type(struct cfg80211_registered_device *rdev,
				    enum nl80211_auth_type auth_type,
				    enum nl80211_commands cmd)
{
	if (auth_type > NL80211_AUTHTYPE_MAX)
		return false;

	switch (cmd) {
	case NL80211_CMD_AUTHENTICATE:
		if (!(rdev->wiphy.features & NL80211_FEATURE_SAE) &&
		    auth_type == NL80211_AUTHTYPE_SAE)
			return false;
		if (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_FILS_STA) &&
		    (auth_type == NL80211_AUTHTYPE_FILS_SK ||
		     auth_type == NL80211_AUTHTYPE_FILS_SK_PFS ||
		     auth_type == NL80211_AUTHTYPE_FILS_PK))
			return false;
		return true;
	case NL80211_CMD_CONNECT:
		if (!(rdev->wiphy.features & NL80211_FEATURE_SAE) &&
		    !wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_SAE_OFFLOAD) &&
		    auth_type == NL80211_AUTHTYPE_SAE)
			return false;

		/* FILS with SK PFS or PK not supported yet */
		if (auth_type == NL80211_AUTHTYPE_FILS_SK_PFS ||
		    auth_type == NL80211_AUTHTYPE_FILS_PK)
			return false;
		if (!wiphy_ext_feature_isset(
			    &rdev->wiphy,
			    NL80211_EXT_FEATURE_FILS_SK_OFFLOAD) &&
		    auth_type == NL80211_AUTHTYPE_FILS_SK)
			return false;
		return true;
	case NL80211_CMD_START_AP:
		/* SAE not supported yet */
		if (auth_type == NL80211_AUTHTYPE_SAE)
			return false;
		/* FILS not supported yet */
		if (auth_type == NL80211_AUTHTYPE_FILS_SK ||
		    auth_type == NL80211_AUTHTYPE_FILS_SK_PFS ||
		    auth_type == NL80211_AUTHTYPE_FILS_PK)
			return false;
		return true;
	default:
		return false;
	}
}