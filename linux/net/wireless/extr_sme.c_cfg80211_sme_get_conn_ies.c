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
typedef  size_t u8 ;
struct wireless_dev {int /*<<< orphan*/  wiphy; } ;
struct TYPE_2__ {size_t extended_capabilities_len; size_t const* extended_capabilities; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (size_t const*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  WLAN_EID_BSS_COEX_2040 133 
 size_t WLAN_EID_EXT_CAPABILITY ; 
#define  WLAN_EID_MOBILITY_DOMAIN 132 
#define  WLAN_EID_QOS_CAPA 131 
#define  WLAN_EID_RRM_ENABLED_CAPABILITIES 130 
#define  WLAN_EID_RSN 129 
#define  WLAN_EID_SUPPORTED_REGULATORY_CLASSES 128 
 scalar_t__ cfg80211_find_ie (size_t,size_t const*,size_t) ; 
 size_t ieee80211_ie_split (size_t const*,size_t,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 size_t* kmemdup (size_t const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t const*,size_t) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_sme_get_conn_ies(struct wireless_dev *wdev,
				     const u8 *ies, size_t ies_len,
				     const u8 **out_ies, size_t *out_ies_len)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	u8 *buf;
	size_t offs;

	if (!rdev->wiphy.extended_capabilities_len ||
	    (ies && cfg80211_find_ie(WLAN_EID_EXT_CAPABILITY, ies, ies_len))) {
		*out_ies = kmemdup(ies, ies_len, GFP_KERNEL);
		if (!*out_ies)
			return -ENOMEM;
		*out_ies_len = ies_len;
		return 0;
	}

	buf = kmalloc(ies_len + rdev->wiphy.extended_capabilities_len + 2,
		      GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	if (ies_len) {
		static const u8 before_extcapa[] = {
			/* not listing IEs expected to be created by driver */
			WLAN_EID_RSN,
			WLAN_EID_QOS_CAPA,
			WLAN_EID_RRM_ENABLED_CAPABILITIES,
			WLAN_EID_MOBILITY_DOMAIN,
			WLAN_EID_SUPPORTED_REGULATORY_CLASSES,
			WLAN_EID_BSS_COEX_2040,
		};

		offs = ieee80211_ie_split(ies, ies_len, before_extcapa,
					  ARRAY_SIZE(before_extcapa), 0);
		memcpy(buf, ies, offs);
		/* leave a whole for extended capabilities IE */
		memcpy(buf + offs + rdev->wiphy.extended_capabilities_len + 2,
		       ies + offs, ies_len - offs);
	} else {
		offs = 0;
	}

	/* place extended capabilities IE (with only driver capabilities) */
	buf[offs] = WLAN_EID_EXT_CAPABILITY;
	buf[offs + 1] = rdev->wiphy.extended_capabilities_len;
	memcpy(buf + offs + 2,
	       rdev->wiphy.extended_capabilities,
	       rdev->wiphy.extended_capabilities_len);

	*out_ies = buf;
	*out_ies_len = ies_len + rdev->wiphy.extended_capabilities_len + 2;

	return 0;
}