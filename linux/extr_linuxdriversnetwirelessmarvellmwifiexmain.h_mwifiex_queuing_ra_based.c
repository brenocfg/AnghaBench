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
struct mwifiex_private {scalar_t__ bss_mode; } ;

/* Variables and functions */
 scalar_t__ GET_BSS_ROLE (struct mwifiex_private*) ; 
 scalar_t__ MWIFIEX_BSS_ROLE_STA ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 

__attribute__((used)) static inline u8
mwifiex_queuing_ra_based(struct mwifiex_private *priv)
{
	/*
	 * Currently we assume if we are in Infra, then DA=RA. This might not be
	 * true in the future
	 */
	if ((priv->bss_mode == NL80211_IFTYPE_STATION ||
	     priv->bss_mode == NL80211_IFTYPE_P2P_CLIENT) &&
	    (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA))
		return false;

	return true;
}