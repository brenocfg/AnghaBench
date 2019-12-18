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
struct regulatory_request {int /*<<< orphan*/  intersect; } ;
struct ieee80211_regdomain {int /*<<< orphan*/ * alpha2; } ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int /*<<< orphan*/  get_cfg80211_regdom () ; 
 int /*<<< orphan*/  is_valid_rd (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_regdomain_info (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  regdom_changes (int /*<<< orphan*/ *) ; 
 struct ieee80211_regdomain* regdom_intersect (struct ieee80211_regdomain const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_regdomains (int,struct ieee80211_regdomain const*) ; 

__attribute__((used)) static int reg_set_rd_user(const struct ieee80211_regdomain *rd,
			   struct regulatory_request *user_request)
{
	const struct ieee80211_regdomain *intersected_rd = NULL;

	if (!regdom_changes(rd->alpha2))
		return -EALREADY;

	if (!is_valid_rd(rd)) {
		pr_err("Invalid regulatory domain detected: %c%c\n",
		       rd->alpha2[0], rd->alpha2[1]);
		print_regdomain_info(rd);
		return -EINVAL;
	}

	if (!user_request->intersect) {
		reset_regdomains(false, rd);
		return 0;
	}

	intersected_rd = regdom_intersect(rd, get_cfg80211_regdom());
	if (!intersected_rd)
		return -EINVAL;

	kfree(rd);
	rd = NULL;
	reset_regdomains(false, intersected_rd);

	return 0;
}