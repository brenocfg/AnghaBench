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
struct wiphy {int regulatory_flags; } ;
struct sk_buff {int dummy; } ;
struct regulatory_request {char* alpha2; scalar_t__ wiphy_idx; scalar_t__ intersect; int /*<<< orphan*/  initiator; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_ATTR_REG_ALPHA2 ; 
 int /*<<< orphan*/  NL80211_ATTR_REG_INITIATOR ; 
 int /*<<< orphan*/  NL80211_ATTR_REG_TYPE ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY_SELF_MANAGED_REG ; 
 int /*<<< orphan*/  NL80211_REGDOM_TYPE_COUNTRY ; 
 int /*<<< orphan*/  NL80211_REGDOM_TYPE_CUSTOM_WORLD ; 
 int /*<<< orphan*/  NL80211_REGDOM_TYPE_INTERSECTION ; 
 int /*<<< orphan*/  NL80211_REGDOM_TYPE_WORLD ; 
 int REGULATORY_WIPHY_SELF_MANAGED ; 
 scalar_t__ WIPHY_IDX_INVALID ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wiphy* wiphy_idx_to_wiphy (scalar_t__) ; 

__attribute__((used)) static bool nl80211_reg_change_event_fill(struct sk_buff *msg,
					  struct regulatory_request *request)
{
	/* Userspace can always count this one always being set */
	if (nla_put_u8(msg, NL80211_ATTR_REG_INITIATOR, request->initiator))
		goto nla_put_failure;

	if (request->alpha2[0] == '0' && request->alpha2[1] == '0') {
		if (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_WORLD))
			goto nla_put_failure;
	} else if (request->alpha2[0] == '9' && request->alpha2[1] == '9') {
		if (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_CUSTOM_WORLD))
			goto nla_put_failure;
	} else if ((request->alpha2[0] == '9' && request->alpha2[1] == '8') ||
		   request->intersect) {
		if (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_INTERSECTION))
			goto nla_put_failure;
	} else {
		if (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_COUNTRY) ||
		    nla_put_string(msg, NL80211_ATTR_REG_ALPHA2,
				   request->alpha2))
			goto nla_put_failure;
	}

	if (request->wiphy_idx != WIPHY_IDX_INVALID) {
		struct wiphy *wiphy = wiphy_idx_to_wiphy(request->wiphy_idx);

		if (wiphy &&
		    nla_put_u32(msg, NL80211_ATTR_WIPHY, request->wiphy_idx))
			goto nla_put_failure;

		if (wiphy &&
		    wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED &&
		    nla_put_flag(msg, NL80211_ATTR_WIPHY_SELF_MANAGED_REG))
			goto nla_put_failure;
	}

	return true;

nla_put_failure:
	return false;
}