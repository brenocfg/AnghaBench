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
typedef  struct ieee80211_regdomain const ieee80211_regdomain ;
struct cfg80211_registered_device {struct ieee80211_regdomain const* requested_regd; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct ieee80211_regdomain const*) ; 
 int PTR_ERR (struct ieee80211_regdomain const*) ; 
 int REGULATORY_WIPHY_SELF_MANAGED ; 
 scalar_t__ WARN (int,char*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  is_valid_rd (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  print_regdomain_info (struct ieee80211_regdomain const*) ; 
 struct ieee80211_regdomain const* reg_copy_regd (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  reg_requests_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

__attribute__((used)) static int __regulatory_set_wiphy_regd(struct wiphy *wiphy,
				       struct ieee80211_regdomain *rd)
{
	const struct ieee80211_regdomain *regd;
	const struct ieee80211_regdomain *prev_regd;
	struct cfg80211_registered_device *rdev;

	if (WARN_ON(!wiphy || !rd))
		return -EINVAL;

	if (WARN(!(wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED),
		 "wiphy should have REGULATORY_WIPHY_SELF_MANAGED\n"))
		return -EPERM;

	if (WARN(!is_valid_rd(rd), "Invalid regulatory domain detected\n")) {
		print_regdomain_info(rd);
		return -EINVAL;
	}

	regd = reg_copy_regd(rd);
	if (IS_ERR(regd))
		return PTR_ERR(regd);

	rdev = wiphy_to_rdev(wiphy);

	spin_lock(&reg_requests_lock);
	prev_regd = rdev->requested_regd;
	rdev->requested_regd = regd;
	spin_unlock(&reg_requests_lock);

	kfree(prev_regd);
	return 0;
}