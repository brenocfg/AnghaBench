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
struct ath10k_vif {int /*<<< orphan*/ * beacon_buf; int /*<<< orphan*/  beacon_paddr; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  dev; int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MAX_FRAME_LEN ; 
 int /*<<< orphan*/  ath10k_mac_vif_beacon_free (struct ath10k_vif*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_mac_vif_beacon_cleanup(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;

	lockdep_assert_held(&ar->data_lock);

	ath10k_mac_vif_beacon_free(arvif);

	if (arvif->beacon_buf) {
		dma_free_coherent(ar->dev, IEEE80211_MAX_FRAME_LEN,
				  arvif->beacon_buf, arvif->beacon_paddr);
		arvif->beacon_buf = NULL;
	}
}