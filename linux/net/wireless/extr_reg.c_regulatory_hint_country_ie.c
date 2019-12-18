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
typedef  int u8 ;
struct wiphy {int dummy; } ;
struct regulatory_request {scalar_t__ initiator; scalar_t__ wiphy_idx; char* alpha2; int country_ie_env; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
typedef  enum environment_cap { ____Placeholder_environment_cap } environment_cap ;

/* Variables and functions */
 int ENVIRON_ANY ; 
 int ENVIRON_INDOOR ; 
 int ENVIRON_OUTDOOR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_COUNTRY_IE_MIN_LEN ; 
 scalar_t__ NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 scalar_t__ WIPHY_IDX_INVALID ; 
 struct regulatory_request* get_last_request () ; 
 scalar_t__ get_wiphy_idx (struct wiphy*) ; 
 int /*<<< orphan*/  kfree (struct regulatory_request*) ; 
 struct regulatory_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_regulatory_request (struct regulatory_request*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  reset_crda_timeouts () ; 
 scalar_t__ unlikely (int) ; 

void regulatory_hint_country_ie(struct wiphy *wiphy, enum nl80211_band band,
				const u8 *country_ie, u8 country_ie_len)
{
	char alpha2[2];
	enum environment_cap env = ENVIRON_ANY;
	struct regulatory_request *request = NULL, *lr;

	/* IE len must be evenly divisible by 2 */
	if (country_ie_len & 0x01)
		return;

	if (country_ie_len < IEEE80211_COUNTRY_IE_MIN_LEN)
		return;

	request = kzalloc(sizeof(*request), GFP_KERNEL);
	if (!request)
		return;

	alpha2[0] = country_ie[0];
	alpha2[1] = country_ie[1];

	if (country_ie[2] == 'I')
		env = ENVIRON_INDOOR;
	else if (country_ie[2] == 'O')
		env = ENVIRON_OUTDOOR;

	rcu_read_lock();
	lr = get_last_request();

	if (unlikely(!lr))
		goto out;

	/*
	 * We will run this only upon a successful connection on cfg80211.
	 * We leave conflict resolution to the workqueue, where can hold
	 * the RTNL.
	 */
	if (lr->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    lr->wiphy_idx != WIPHY_IDX_INVALID)
		goto out;

	request->wiphy_idx = get_wiphy_idx(wiphy);
	request->alpha2[0] = alpha2[0];
	request->alpha2[1] = alpha2[1];
	request->initiator = NL80211_REGDOM_SET_BY_COUNTRY_IE;
	request->country_ie_env = env;

	/* Allow calling CRDA again */
	reset_crda_timeouts();

	queue_regulatory_request(request);
	request = NULL;
out:
	kfree(request);
	rcu_read_unlock();
}