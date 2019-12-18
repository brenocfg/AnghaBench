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
struct ieee80211_local {int /*<<< orphan*/  wep_iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_WEP_IV_LEN ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ieee80211_wep_init(struct ieee80211_local *local)
{
	/* start WEP IV from a random value */
	get_random_bytes(&local->wep_iv, IEEE80211_WEP_IV_LEN);

	return 0;
}