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
struct wiphy {int /*<<< orphan*/  regulatory_flags; } ;
struct regulatory_request {char* alpha2; int /*<<< orphan*/  initiator; int /*<<< orphan*/  wiphy_idx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_REGDOM_SET_BY_DRIVER ; 
 int /*<<< orphan*/  REGULATORY_CUSTOM_REG ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  get_wiphy_idx (struct wiphy*) ; 
 struct regulatory_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_regulatory_request (struct regulatory_request*) ; 
 int /*<<< orphan*/  reset_crda_timeouts () ; 

int regulatory_hint(struct wiphy *wiphy, const char *alpha2)
{
	struct regulatory_request *request;

	if (WARN_ON(!alpha2 || !wiphy))
		return -EINVAL;

	wiphy->regulatory_flags &= ~REGULATORY_CUSTOM_REG;

	request = kzalloc(sizeof(struct regulatory_request), GFP_KERNEL);
	if (!request)
		return -ENOMEM;

	request->wiphy_idx = get_wiphy_idx(wiphy);

	request->alpha2[0] = alpha2[0];
	request->alpha2[1] = alpha2[1];
	request->initiator = NL80211_REGDOM_SET_BY_DRIVER;

	/* Allow calling CRDA again */
	reset_crda_timeouts();

	queue_regulatory_request(request);

	return 0;
}