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
typedef  int u32 ;
struct nl80211_sta_flag_update {int mask; int set; } ;
struct station_info {struct nl80211_sta_flag_update sta_flags; int /*<<< orphan*/  filled; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 int BRCMF_STA_ASSOC ; 
 int BRCMF_STA_AUTHE ; 
 int BRCMF_STA_AUTHO ; 
 int BRCMF_STA_WME ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_ASSOCIATED ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_AUTHENTICATED ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_AUTHORIZED ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_WME ; 
 int /*<<< orphan*/  NL80211_STA_INFO_STA_FLAGS ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void brcmf_convert_sta_flags(u32 fw_sta_flags, struct station_info *si)
{
	struct nl80211_sta_flag_update *sfu;

	brcmf_dbg(TRACE, "flags %08x\n", fw_sta_flags);
	si->filled |= BIT_ULL(NL80211_STA_INFO_STA_FLAGS);
	sfu = &si->sta_flags;
	sfu->mask = BIT(NL80211_STA_FLAG_WME) |
		    BIT(NL80211_STA_FLAG_AUTHENTICATED) |
		    BIT(NL80211_STA_FLAG_ASSOCIATED) |
		    BIT(NL80211_STA_FLAG_AUTHORIZED);
	if (fw_sta_flags & BRCMF_STA_WME)
		sfu->set |= BIT(NL80211_STA_FLAG_WME);
	if (fw_sta_flags & BRCMF_STA_AUTHE)
		sfu->set |= BIT(NL80211_STA_FLAG_AUTHENTICATED);
	if (fw_sta_flags & BRCMF_STA_ASSOC)
		sfu->set |= BIT(NL80211_STA_FLAG_ASSOCIATED);
	if (fw_sta_flags & BRCMF_STA_AUTHO)
		sfu->set |= BIT(NL80211_STA_FLAG_AUTHORIZED);
}