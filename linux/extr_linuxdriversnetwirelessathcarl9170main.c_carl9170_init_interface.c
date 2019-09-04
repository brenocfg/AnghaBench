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
struct ieee80211_vif {scalar_t__ type; int p2p; int /*<<< orphan*/  addr; } ;
struct ath_common {int /*<<< orphan*/  macaddr; } ;
struct ar9170 {int disable_offload; int rx_software_decryption; struct ath_common common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IS_STARTED (struct ar9170*) ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int carl9170_set_operating_mode (struct ar9170*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int carl9170_init_interface(struct ar9170 *ar,
				   struct ieee80211_vif *vif)
{
	struct ath_common *common = &ar->common;
	int err;

	if (!vif) {
		WARN_ON_ONCE(IS_STARTED(ar));
		return 0;
	}

	memcpy(common->macaddr, vif->addr, ETH_ALEN);

	/* We have to fall back to software crypto, whenever
	 * the user choose to participates in an IBSS. HW
	 * offload for IBSS RSN is not supported by this driver.
	 *
	 * NOTE: If the previous main interface has already
	 * disabled hw crypto offload, we have to keep this
	 * previous disable_offload setting as it was.
	 * Altough ideally, we should notify mac80211 and tell
	 * it to forget about any HW crypto offload for now.
	 */
	ar->disable_offload |= ((vif->type != NL80211_IFTYPE_STATION) &&
	    (vif->type != NL80211_IFTYPE_AP));

	/* While the driver supports HW offload in a single
	 * P2P client configuration, it doesn't support HW
	 * offload in the favourit, concurrent P2P GO+CLIENT
	 * configuration. Hence, HW offload will always be
	 * disabled for P2P.
	 */
	ar->disable_offload |= vif->p2p;

	ar->rx_software_decryption = ar->disable_offload;

	err = carl9170_set_operating_mode(ar);
	return err;
}