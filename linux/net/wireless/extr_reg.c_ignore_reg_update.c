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
struct wiphy {int regulatory_flags; int /*<<< orphan*/  regd; } ;
struct regulatory_request {int /*<<< orphan*/  alpha2; } ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;

/* Variables and functions */
 int NL80211_REGDOM_SET_BY_CORE ; 
 int NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 int REGULATORY_CUSTOM_REG ; 
 int REGULATORY_WIPHY_SELF_MANAGED ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  is_world_regdom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int reg_dev_ignore_cell_hint (struct wiphy*) ; 
 int /*<<< orphan*/  reg_initiator_name (int) ; 
 scalar_t__ reg_request_cell_base (struct regulatory_request*) ; 
 scalar_t__ wiphy_strict_alpha2_regd (struct wiphy*) ; 

__attribute__((used)) static bool ignore_reg_update(struct wiphy *wiphy,
			      enum nl80211_reg_initiator initiator)
{
	struct regulatory_request *lr = get_last_request();

	if (wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED)
		return true;

	if (!lr) {
		pr_debug("Ignoring regulatory request set by %s since last_request is not set\n",
			 reg_initiator_name(initiator));
		return true;
	}

	if (initiator == NL80211_REGDOM_SET_BY_CORE &&
	    wiphy->regulatory_flags & REGULATORY_CUSTOM_REG) {
		pr_debug("Ignoring regulatory request set by %s since the driver uses its own custom regulatory domain\n",
			 reg_initiator_name(initiator));
		return true;
	}

	/*
	 * wiphy->regd will be set once the device has its own
	 * desired regulatory domain set
	 */
	if (wiphy_strict_alpha2_regd(wiphy) && !wiphy->regd &&
	    initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    !is_world_regdom(lr->alpha2)) {
		pr_debug("Ignoring regulatory request set by %s since the driver requires its own regulatory domain to be set first\n",
			 reg_initiator_name(initiator));
		return true;
	}

	if (reg_request_cell_base(lr))
		return reg_dev_ignore_cell_hint(wiphy);

	return false;
}