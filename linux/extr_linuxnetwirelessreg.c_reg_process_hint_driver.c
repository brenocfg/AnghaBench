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
struct wiphy {int /*<<< orphan*/  regd; } ;
struct regulatory_request {int intersect; int processed; } ;
struct ieee80211_regdomain {int dummy; } ;
typedef  enum reg_request_treatment { ____Placeholder_reg_request_treatment } reg_request_treatment ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct ieee80211_regdomain const*) ; 
#define  REG_REQ_ALREADY_SET 131 
#define  REG_REQ_IGNORE 130 
#define  REG_REQ_INTERSECT 129 
#define  REG_REQ_OK 128 
 int __reg_process_hint_driver (struct regulatory_request*) ; 
 int /*<<< orphan*/  get_cfg80211_regdom () ; 
 struct ieee80211_regdomain* get_wiphy_regdom (struct wiphy*) ; 
 int /*<<< orphan*/  nl80211_send_reg_change_event (struct regulatory_request*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  rcu_free_regdom (struct ieee80211_regdomain const*) ; 
 struct ieee80211_regdomain* reg_copy_regd (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_query_database (struct regulatory_request*) ; 
 int /*<<< orphan*/  reg_set_request_processed () ; 
 int /*<<< orphan*/  reg_update_last_request (struct regulatory_request*) ; 

__attribute__((used)) static enum reg_request_treatment
reg_process_hint_driver(struct wiphy *wiphy,
			struct regulatory_request *driver_request)
{
	const struct ieee80211_regdomain *regd, *tmp;
	enum reg_request_treatment treatment;

	treatment = __reg_process_hint_driver(driver_request);

	switch (treatment) {
	case REG_REQ_OK:
		break;
	case REG_REQ_IGNORE:
		return REG_REQ_IGNORE;
	case REG_REQ_INTERSECT:
	case REG_REQ_ALREADY_SET:
		regd = reg_copy_regd(get_cfg80211_regdom());
		if (IS_ERR(regd))
			return REG_REQ_IGNORE;

		tmp = get_wiphy_regdom(wiphy);
		rcu_assign_pointer(wiphy->regd, regd);
		rcu_free_regdom(tmp);
	}


	driver_request->intersect = treatment == REG_REQ_INTERSECT;
	driver_request->processed = false;

	/*
	 * Since CRDA will not be called in this case as we already
	 * have applied the requested regulatory domain before we just
	 * inform userspace we have processed the request
	 */
	if (treatment == REG_REQ_ALREADY_SET) {
		nl80211_send_reg_change_event(driver_request);
		reg_update_last_request(driver_request);
		reg_set_request_processed();
		return REG_REQ_ALREADY_SET;
	}

	if (reg_query_database(driver_request)) {
		reg_update_last_request(driver_request);
		return REG_REQ_OK;
	}

	return REG_REQ_IGNORE;
}