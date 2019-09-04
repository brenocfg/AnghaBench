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
struct regulatory_request {scalar_t__ intersect; int /*<<< orphan*/  wiphy_idx; } ;
struct ieee80211_regdomain {int /*<<< orphan*/ * alpha2; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  is_alpha2_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_an_alpha2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_unknown_alpha2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_rd (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_regdomain_info (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  reset_regdomains (int,struct ieee80211_regdomain const*) ; 
 struct wiphy* wiphy_idx_to_wiphy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_set_rd_country_ie(const struct ieee80211_regdomain *rd,
				 struct regulatory_request *country_ie_request)
{
	struct wiphy *request_wiphy;

	if (!is_alpha2_set(rd->alpha2) && !is_an_alpha2(rd->alpha2) &&
	    !is_unknown_alpha2(rd->alpha2))
		return -EINVAL;

	/*
	 * Lets only bother proceeding on the same alpha2 if the current
	 * rd is non static (it means CRDA was present and was used last)
	 * and the pending request came in from a country IE
	 */

	if (!is_valid_rd(rd)) {
		pr_err("Invalid regulatory domain detected: %c%c\n",
		       rd->alpha2[0], rd->alpha2[1]);
		print_regdomain_info(rd);
		return -EINVAL;
	}

	request_wiphy = wiphy_idx_to_wiphy(country_ie_request->wiphy_idx);
	if (!request_wiphy)
		return -ENODEV;

	if (country_ie_request->intersect)
		return -EINVAL;

	reset_regdomains(false, rd);
	return 0;
}