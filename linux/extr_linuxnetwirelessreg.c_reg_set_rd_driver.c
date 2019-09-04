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
struct regulatory_request {int /*<<< orphan*/  intersect; int /*<<< orphan*/  wiphy_idx; } ;
struct ieee80211_regdomain {int /*<<< orphan*/ * alpha2; } ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct ieee80211_regdomain const*) ; 
 int PTR_ERR (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  get_cfg80211_regdom () ; 
 struct ieee80211_regdomain* get_wiphy_regdom (struct wiphy*) ; 
 int /*<<< orphan*/  is_valid_rd (struct ieee80211_regdomain const*) ; 
 scalar_t__ is_world_regdom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_regdomain_info (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  rcu_free_regdom (struct ieee80211_regdomain const*) ; 
 struct ieee80211_regdomain* reg_copy_regd (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  regdom_changes (int /*<<< orphan*/ *) ; 
 struct ieee80211_regdomain* regdom_intersect (struct ieee80211_regdomain const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_regdomains (int,struct ieee80211_regdomain const*) ; 
 struct wiphy* wiphy_idx_to_wiphy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_set_rd_driver(const struct ieee80211_regdomain *rd,
			     struct regulatory_request *driver_request)
{
	const struct ieee80211_regdomain *regd;
	const struct ieee80211_regdomain *intersected_rd = NULL;
	const struct ieee80211_regdomain *tmp;
	struct wiphy *request_wiphy;

	if (is_world_regdom(rd->alpha2))
		return -EINVAL;

	if (!regdom_changes(rd->alpha2))
		return -EALREADY;

	if (!is_valid_rd(rd)) {
		pr_err("Invalid regulatory domain detected: %c%c\n",
		       rd->alpha2[0], rd->alpha2[1]);
		print_regdomain_info(rd);
		return -EINVAL;
	}

	request_wiphy = wiphy_idx_to_wiphy(driver_request->wiphy_idx);
	if (!request_wiphy)
		return -ENODEV;

	if (!driver_request->intersect) {
		if (request_wiphy->regd)
			return -EALREADY;

		regd = reg_copy_regd(rd);
		if (IS_ERR(regd))
			return PTR_ERR(regd);

		rcu_assign_pointer(request_wiphy->regd, regd);
		reset_regdomains(false, rd);
		return 0;
	}

	intersected_rd = regdom_intersect(rd, get_cfg80211_regdom());
	if (!intersected_rd)
		return -EINVAL;

	/*
	 * We can trash what CRDA provided now.
	 * However if a driver requested this specific regulatory
	 * domain we keep it for its private use
	 */
	tmp = get_wiphy_regdom(request_wiphy);
	rcu_assign_pointer(request_wiphy->regd, rd);
	rcu_free_regdom(tmp);

	rd = NULL;

	reset_regdomains(false, intersected_rd);

	return 0;
}