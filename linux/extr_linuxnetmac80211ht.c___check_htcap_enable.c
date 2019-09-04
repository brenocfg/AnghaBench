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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_sta_ht_cap {int /*<<< orphan*/  cap; } ;
struct ieee80211_ht_cap {int cap_info; } ;
typedef  int __le16 ;

/* Variables and functions */
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __check_htcap_enable(struct ieee80211_ht_cap *ht_capa,
				  struct ieee80211_ht_cap *ht_capa_mask,
				  struct ieee80211_sta_ht_cap *ht_cap,
				  u16 flag)
{
	__le16 le_flag = cpu_to_le16(flag);

	if ((ht_capa_mask->cap_info & le_flag) &&
	    (ht_capa->cap_info & le_flag))
		ht_cap->cap |= flag;
}