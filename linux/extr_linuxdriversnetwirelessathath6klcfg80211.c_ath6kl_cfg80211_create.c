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
struct ath6kl {struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_cfg80211_ops ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 struct wiphy* wiphy_new (int /*<<< orphan*/ *,int) ; 
 struct ath6kl* wiphy_priv (struct wiphy*) ; 

struct ath6kl *ath6kl_cfg80211_create(void)
{
	struct ath6kl *ar;
	struct wiphy *wiphy;

	/* create a new wiphy for use with cfg80211 */
	wiphy = wiphy_new(&ath6kl_cfg80211_ops, sizeof(struct ath6kl));

	if (!wiphy) {
		ath6kl_err("couldn't allocate wiphy device\n");
		return NULL;
	}

	ar = wiphy_priv(wiphy);
	ar->wiphy = wiphy;

	return ar;
}