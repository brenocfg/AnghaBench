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
struct ieee80211_hdr {int /*<<< orphan*/  addr4; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FCTL_TODS ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ieee80211_fill_mesh_addresses(struct ieee80211_hdr *hdr, __le16 *fc,
				  const u8 *meshda, const u8 *meshsa)
{
	if (is_multicast_ether_addr(meshda)) {
		*fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS);
		/* DA TA SA */
		memcpy(hdr->addr1, meshda, ETH_ALEN);
		memcpy(hdr->addr2, meshsa, ETH_ALEN);
		memcpy(hdr->addr3, meshsa, ETH_ALEN);
		return 24;
	} else {
		*fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS);
		/* RA TA DA SA */
		eth_zero_addr(hdr->addr1);   /* RA is resolved later */
		memcpy(hdr->addr2, meshsa, ETH_ALEN);
		memcpy(hdr->addr3, meshda, ETH_ALEN);
		memcpy(hdr->addr4, meshsa, ETH_ALEN);
		return 30;
	}
}