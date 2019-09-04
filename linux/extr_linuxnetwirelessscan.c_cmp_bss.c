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
typedef  scalar_t__ u8 ;
struct cfg80211_bss_ies {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct cfg80211_bss {scalar_t__ const* bssid; int /*<<< orphan*/  capability; int /*<<< orphan*/  ies; TYPE_1__* channel; } ;
typedef  enum bss_compare_mode { ____Placeholder_bss_compare_mode } bss_compare_mode ;
struct TYPE_2__ {int center_freq; } ;

/* Variables and functions */
#define  BSS_CMP_HIDE_NUL 130 
#define  BSS_CMP_HIDE_ZLEN 129 
#define  BSS_CMP_REGULAR 128 
 scalar_t__ WLAN_CAPABILITY_IS_STA_BSS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_MESH_CONFIG ; 
 int /*<<< orphan*/  WLAN_EID_MESH_ID ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 scalar_t__* cfg80211_find_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memcmp (scalar_t__ const*,scalar_t__ const*,scalar_t__ const) ; 
 struct cfg80211_bss_ies* rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_bss(struct cfg80211_bss *a,
		   struct cfg80211_bss *b,
		   enum bss_compare_mode mode)
{
	const struct cfg80211_bss_ies *a_ies, *b_ies;
	const u8 *ie1 = NULL;
	const u8 *ie2 = NULL;
	int i, r;

	if (a->channel != b->channel)
		return b->channel->center_freq - a->channel->center_freq;

	a_ies = rcu_access_pointer(a->ies);
	if (!a_ies)
		return -1;
	b_ies = rcu_access_pointer(b->ies);
	if (!b_ies)
		return 1;

	if (WLAN_CAPABILITY_IS_STA_BSS(a->capability))
		ie1 = cfg80211_find_ie(WLAN_EID_MESH_ID,
				       a_ies->data, a_ies->len);
	if (WLAN_CAPABILITY_IS_STA_BSS(b->capability))
		ie2 = cfg80211_find_ie(WLAN_EID_MESH_ID,
				       b_ies->data, b_ies->len);
	if (ie1 && ie2) {
		int mesh_id_cmp;

		if (ie1[1] == ie2[1])
			mesh_id_cmp = memcmp(ie1 + 2, ie2 + 2, ie1[1]);
		else
			mesh_id_cmp = ie2[1] - ie1[1];

		ie1 = cfg80211_find_ie(WLAN_EID_MESH_CONFIG,
				       a_ies->data, a_ies->len);
		ie2 = cfg80211_find_ie(WLAN_EID_MESH_CONFIG,
				       b_ies->data, b_ies->len);
		if (ie1 && ie2) {
			if (mesh_id_cmp)
				return mesh_id_cmp;
			if (ie1[1] != ie2[1])
				return ie2[1] - ie1[1];
			return memcmp(ie1 + 2, ie2 + 2, ie1[1]);
		}
	}

	r = memcmp(a->bssid, b->bssid, sizeof(a->bssid));
	if (r)
		return r;

	ie1 = cfg80211_find_ie(WLAN_EID_SSID, a_ies->data, a_ies->len);
	ie2 = cfg80211_find_ie(WLAN_EID_SSID, b_ies->data, b_ies->len);

	if (!ie1 && !ie2)
		return 0;

	/*
	 * Note that with "hide_ssid", the function returns a match if
	 * the already-present BSS ("b") is a hidden SSID beacon for
	 * the new BSS ("a").
	 */

	/* sort missing IE before (left of) present IE */
	if (!ie1)
		return -1;
	if (!ie2)
		return 1;

	switch (mode) {
	case BSS_CMP_HIDE_ZLEN:
		/*
		 * In ZLEN mode we assume the BSS entry we're
		 * looking for has a zero-length SSID. So if
		 * the one we're looking at right now has that,
		 * return 0. Otherwise, return the difference
		 * in length, but since we're looking for the
		 * 0-length it's really equivalent to returning
		 * the length of the one we're looking at.
		 *
		 * No content comparison is needed as we assume
		 * the content length is zero.
		 */
		return ie2[1];
	case BSS_CMP_REGULAR:
	default:
		/* sort by length first, then by contents */
		if (ie1[1] != ie2[1])
			return ie2[1] - ie1[1];
		return memcmp(ie1 + 2, ie2 + 2, ie1[1]);
	case BSS_CMP_HIDE_NUL:
		if (ie1[1] != ie2[1])
			return ie2[1] - ie1[1];
		/* this is equivalent to memcmp(zeroes, ie2 + 2, len) */
		for (i = 0; i < ie2[1]; i++)
			if (ie2[i + 2])
				return -1;
		return 0;
	}
}