#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int n_cipher_schemes; struct ieee80211_cipher_scheme* cipher_schemes; } ;
struct ieee80211_local {TYPE_1__ hw; } ;
struct ieee80211_cipher_scheme {scalar_t__ cipher; int iftype; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int BIT (int) ; 

const struct ieee80211_cipher_scheme *
ieee80211_cs_get(struct ieee80211_local *local, u32 cipher,
		 enum nl80211_iftype iftype)
{
	const struct ieee80211_cipher_scheme *l = local->hw.cipher_schemes;
	int n = local->hw.n_cipher_schemes;
	int i;
	const struct ieee80211_cipher_scheme *cs = NULL;

	for (i = 0; i < n; i++) {
		if (l[i].cipher == cipher) {
			cs = &l[i];
			break;
		}
	}

	if (!cs || !(cs->iftype & BIT(iftype)))
		return NULL;

	return cs;
}