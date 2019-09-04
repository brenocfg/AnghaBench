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
struct regulatory_request {int initiator; scalar_t__ wiphy_idx; } ;
typedef  enum reg_request_treatment { ____Placeholder_reg_request_treatment } reg_request_treatment ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;

/* Variables and functions */
#define  NL80211_REGDOM_SET_BY_CORE 131 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 130 
#define  NL80211_REGDOM_SET_BY_DRIVER 129 
#define  NL80211_REGDOM_SET_BY_USER 128 
 int REGULATORY_STRICT_REG ; 
 int REG_REQ_ALREADY_SET ; 
 int REG_REQ_IGNORE ; 
 int REG_REQ_OK ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 scalar_t__ WIPHY_IDX_INVALID ; 
 int /*<<< orphan*/  reg_check_channels () ; 
 int /*<<< orphan*/  reg_free_request (struct regulatory_request*) ; 
 int reg_process_hint_core (struct regulatory_request*) ; 
 int reg_process_hint_country_ie (struct wiphy*,struct regulatory_request*) ; 
 int reg_process_hint_driver (struct wiphy*,struct regulatory_request*) ; 
 int reg_process_hint_user (struct regulatory_request*) ; 
 int /*<<< orphan*/  wiphy_all_share_dfs_chan_state (struct wiphy*) ; 
 struct wiphy* wiphy_idx_to_wiphy (scalar_t__) ; 
 int /*<<< orphan*/  wiphy_update_regulatory (struct wiphy*,int) ; 

__attribute__((used)) static void reg_process_hint(struct regulatory_request *reg_request)
{
	struct wiphy *wiphy = NULL;
	enum reg_request_treatment treatment;
	enum nl80211_reg_initiator initiator = reg_request->initiator;

	if (reg_request->wiphy_idx != WIPHY_IDX_INVALID)
		wiphy = wiphy_idx_to_wiphy(reg_request->wiphy_idx);

	switch (initiator) {
	case NL80211_REGDOM_SET_BY_CORE:
		treatment = reg_process_hint_core(reg_request);
		break;
	case NL80211_REGDOM_SET_BY_USER:
		treatment = reg_process_hint_user(reg_request);
		break;
	case NL80211_REGDOM_SET_BY_DRIVER:
		if (!wiphy)
			goto out_free;
		treatment = reg_process_hint_driver(wiphy, reg_request);
		break;
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		if (!wiphy)
			goto out_free;
		treatment = reg_process_hint_country_ie(wiphy, reg_request);
		break;
	default:
		WARN(1, "invalid initiator %d\n", initiator);
		goto out_free;
	}

	if (treatment == REG_REQ_IGNORE)
		goto out_free;

	WARN(treatment != REG_REQ_OK && treatment != REG_REQ_ALREADY_SET,
	     "unexpected treatment value %d\n", treatment);

	/* This is required so that the orig_* parameters are saved.
	 * NOTE: treatment must be set for any case that reaches here!
	 */
	if (treatment == REG_REQ_ALREADY_SET && wiphy &&
	    wiphy->regulatory_flags & REGULATORY_STRICT_REG) {
		wiphy_update_regulatory(wiphy, initiator);
		wiphy_all_share_dfs_chan_state(wiphy);
		reg_check_channels();
	}

	return;

out_free:
	reg_free_request(reg_request);
}