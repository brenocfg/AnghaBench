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
typedef  int /*<<< orphan*/  u8 ;
struct cfg80211_bss_ies {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct cfg80211_bss {int /*<<< orphan*/  ies; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* cfg80211_find_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cfg80211_bss_ies* rcu_dereference (int /*<<< orphan*/ ) ; 

const u8 *ieee80211_bss_get_ie(struct cfg80211_bss *bss, u8 ie)
{
	const struct cfg80211_bss_ies *ies;

	ies = rcu_dereference(bss->ies);
	if (!ies)
		return NULL;

	return cfg80211_find_ie(ie, ies->data, ies->len);
}