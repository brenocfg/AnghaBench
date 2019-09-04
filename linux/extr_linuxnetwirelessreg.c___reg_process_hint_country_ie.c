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
struct regulatory_request {scalar_t__ initiator; int /*<<< orphan*/  alpha2; int /*<<< orphan*/  wiphy_idx; } ;
typedef  enum reg_request_treatment { ____Placeholder_reg_request_treatment } reg_request_treatment ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 int REGULATORY_COUNTRY_IE_IGNORE ; 
 int REG_REQ_ALREADY_SET ; 
 int REG_REQ_IGNORE ; 
 int REG_REQ_OK ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  is_an_alpha2 (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_request_cell_base (struct regulatory_request*) ; 
 scalar_t__ regdom_changes (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct wiphy* wiphy_idx_to_wiphy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum reg_request_treatment
__reg_process_hint_country_ie(struct wiphy *wiphy,
			      struct regulatory_request *country_ie_request)
{
	struct wiphy *last_wiphy = NULL;
	struct regulatory_request *lr = get_last_request();

	if (reg_request_cell_base(lr)) {
		/* Trust a Cell base station over the AP's country IE */
		if (regdom_changes(country_ie_request->alpha2))
			return REG_REQ_IGNORE;
		return REG_REQ_ALREADY_SET;
	} else {
		if (wiphy->regulatory_flags & REGULATORY_COUNTRY_IE_IGNORE)
			return REG_REQ_IGNORE;
	}

	if (unlikely(!is_an_alpha2(country_ie_request->alpha2)))
		return -EINVAL;

	if (lr->initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE)
		return REG_REQ_OK;

	last_wiphy = wiphy_idx_to_wiphy(lr->wiphy_idx);

	if (last_wiphy != wiphy) {
		/*
		 * Two cards with two APs claiming different
		 * Country IE alpha2s. We could
		 * intersect them, but that seems unlikely
		 * to be correct. Reject second one for now.
		 */
		if (regdom_changes(country_ie_request->alpha2))
			return REG_REQ_IGNORE;
		return REG_REQ_ALREADY_SET;
	}

	if (regdom_changes(country_ie_request->alpha2))
		return REG_REQ_OK;
	return REG_REQ_ALREADY_SET;
}